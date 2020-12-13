#include "Map.h"

Map::Map(Player& p, int roomCount) : player(p), roomCount(roomCount), currentRoom(0), titleTexture(NULL)
{
	rooms = new Room * [roomCount];
}

Map::~Map()
{
	for (int i = 0; i < roomCount; i++)
	{
		delete rooms[i];
	}
	delete[] rooms;
}

Map::Map(string worldName, Player& p, RenderContext& renderer, int* startMap, int startRoom) : 
	player(p), worldName(worldName)
{
	// First we determine whether the files representing the world need to be generated, that is to say whether these files don't exist or whether they are older than the file representing the world.
	struct stat dataLocation;
	struct stat world;
	struct stat data;

	if (stat((WORLDDATA_LOCATION).c_str(), &dataLocation) != 0)
	{
		string d = "./Data/";
		mkdir(d.c_str(), 0777);
		mkdir((WORLDDATA_LOCATION).c_str(), 0777);
	}

	if (stat((WORLDFILES_LOCATION + worldName + EXT).c_str(), &world) != 0)
	{
		cout << WORLDFILES_LOCATION + worldName + EXT << " doesn't exist..." << endl;
		return;
	}
	if (stat((WORLDDATA_LOCATION + worldName + "/" + worldName + "Start" + EXT).c_str(), &data) != 0)
	{
		mkdir((WORLDDATA_LOCATION + worldName + "/").c_str(), 0777);
		worldFromFile(worldName);
	}
	else
	{
		auto worldTime = world.st_mtime;
		auto dataTime = data.st_mtime;
		if (dataTime < worldTime)
			worldFromFile(worldName);
	}
	mapFromFiles(worldName, p, renderer, startMap, startRoom);
	if (DEBUG_MODE)
		titleTexture = LoadString("CURRENT MAP : " + worldName, renderer);
}

void Map::render(RenderContext& renderer, int offsetX, int offsetY)
{
	Room* cur = rooms[currentRoom];

	int offX = offsetX - cur->getX() + (BLOCKS_W - cur->getW()) / 2;
	int offY = offsetY - cur->getY() + (BLOCKS_H - cur->getH()) / 2;

	cur->render(renderer, offX, offY);

	for (int i = 0; i < roomCount; i++)
	{
		if (i != currentRoom)
		{
			rooms[i]->render(renderer, offX, offY);
		}
	}

	player.render(renderer, offX + cur->getX(), offY + cur->getY());

	if (DEBUG_MODE && titleTexture != NULL)
	{
		titleTexture->renderUnscaled(renderer, 0, 0);
		LoadString("Room : " + to_string(currentRoom), renderer, 0x00FFffff)->renderUnscaled(renderer, 0, 16);
	}
}

void Map::tick(int time, GAME* game)
{
	rooms[currentRoom]->tick(time, game);
}

int Map::getRoomCount()
{
	return roomCount;
}

Room** Map::getRooms()
{
	return rooms;
}

int Map::getCurrentRoom()
{
	return currentRoom;
}

Room& Map::getCurrentRoomObject()
{
	return *(getRooms()[currentRoom]);
}

void Map::onKeyDown(GAME* game)
{
	rooms[currentRoom]->onKeyDown(game);
}

void Map::onMouseEvent(MOUSE_DATA* md)
{

}

void Map::worldFromFile(string worldName)
{
	int NumberOfMaps;
	string line;
	string newFile = WORLDDATA_LOCATION + worldName + "/" + worldName; //A string we will use often
	ifstream World(WORLDFILES_LOCATION + worldName + EXT);

	getline(World, line);
	NumberOfMaps = stoi(line);

	ofstream start(newFile + "Start" + EXT); //We create a new file in which we will detail the start position and characteristics of the player
	for (int map = 0; map < NumberOfMaps; map++)
	{
		if (!intlParseMap(newFile, map, World, start))
			return;
	}
	World.close();
}

bool Map::intlParseMap(string& newFile, int map, ifstream& World, ofstream& start)
{
	string line;
	ofstream layout(newFile + to_string(map) + EXT);
	ofstream data(newFile + to_string(map) + "Data" + EXT);

	getline(World, line);
	if (line.length() <= 1 || line[0] != '#' || line[1] != '#')
		cout << "Expected ## before beginning of map " << map << " in " << newFile << endl;

	getline(World, line);
	int NumberOfRooms = stoi(line);
	layout << to_string(NumberOfRooms) << endl;

	for (int room = 0; room < NumberOfRooms; room++)
	{
		{
			if (!intlParseRoom(newFile, World, map, room, layout, start, data))
				return false;
		}
	}
	layout.close();
	data.close();
	return true;
}

bool Map::intlParseRoom(string& newFile, ifstream& World, int map, int room, ofstream& layout, ofstream& start, ofstream& data)
{
	int height, width;
	string line;
	getline(World, line);
	if (line.length() == 0 || line[0] != '#')
	{
		cout << "Expected # before beginning of room " << room << " in map " << map << " in " << newFile << endl;
		return false;
	}

	/* We determine the dimensions of the room. */
	getline(World, line);
	size_t h;
	width = stoi(line, &h);
	line.erase(0, h);
	height = stoi(line);

	layout << to_string(width) << " " << to_string(height) << endl;

	/* We determine the absolute position of the room. */
	int x, y;
	getline(World, line);
	x = stoi(line, &h);
	line.erase(0, h);
	y = stoi(line);

	layout << to_string(x) << " " << to_string(y) << endl;

	string descriptions = "";
	int headerLength = 0;

	getline(World, line);

	while (line.length() == 0 || line[0] != '#')
	{
		if (line != "")
		{
			descriptions += line + "\n";
			headerLength += 1;
		}
		getline(World, line);
	}

	/*This array will contain each non-empty line between the absolute position of
	the room and the next line starting with #, that is to say all the additional
	information needed to describe objects and entities (or anything else that is
	added), such as contents of chests, characteristics of monsters, that are in
	the room.*/
	string* header = new string[headerLength];

	for (int i = 0; i < headerLength; i++)
	{
		size_t firstlineskip = descriptions.find("\n");
		header[i] = descriptions.substr(0, firstlineskip);
		descriptions.erase(0, firstlineskip + 1);
	}

	/*Block parsing (for player start block)*/
	for (int i = 0; i < height; i++)
	{
		getline(World, line);
		if (line[line.length() - 1] == '\r')
		{
			line.erase(line.length() - 1);
		}
		string extraspaces = string(max(0, width * 3 - int(line.length())), ' ');
		line += extraspaces; //We add extra spaces so that all lines in the file are of the same length : width*3. If we find an empty space, it is an empty block.
		for (size_t j = 0; j < width; j++)
		{
			layout << line[3 * j];
			switch (line[3 * j + 1])
			{
			case ' ':
				break;
			case 'p':
				start << to_string(map) << " " << to_string(room) << " " << to_string(j) << " " << to_string(i) << endl;
				for (int k = 0; k < headerLength; k++)
				{ //There may be information in the header as to what health or items the player starts with for example
					if (header[k][0] == 'p')
					{
						start << header[k].erase(0);
					}
				}
				start.close();
				break;
			default:
				data << to_string(room) << " " << to_string(j) << " " << to_string(i) << " ";
				bool notinheader = true;
				for (int k = 0; k < headerLength; k++)
				{
					if (header[k][0] == line[3 * j + 1] && header[k][1] == line[3 * j + 2])
					{
						data << header[k] << endl;
						notinheader = false;
						break;
					}
				}
				if (notinheader)
				{
					data << line[3 * j + 1] << line[3 * j + 2] << endl;
				}
				break;
			}
		}
		layout << endl;
	}
	delete[] header;
	return true;
}

void Map::mapFromFiles(string worldName, Player& p, RenderContext& renderer, int* startMap, int startRoom)
{
	string filename = WORLDDATA_LOCATION + worldName + "/" + worldName;
	ifstream start(filename + "Start" + EXT);
	string line;
	size_t a;
	int startX, startY;

	/*
	TODO : Explications here
	*/
	if (*startMap == -1)
	{
		if (not getline(start, line))
		{
			cout << "No initial position for player found in " << filename << endl;
			startX = 1;
			startY = 1; //TODO This doesnt work !
		}
		else {
			*startMap = stoi(line, &a);
			line.erase(0, a);
			startRoom = stoi(line, &a);
			line.erase(0, a);
			startX = stoi(line, &a);
			line.erase(0, a);
			startY = stoi(line);
		}
		player.teleport(startX, startY);
	}
	//TODO other player characteristics
	start.close();
	ifstream layout(filename + to_string(*startMap) + EXT);
	ifstream data(filename + to_string(*startMap) + "Data" + EXT);

	getline(layout, line);
	roomCount = stoi(line);

	rooms = new Room * [roomCount];
	currentRoom = startRoom;

	for (int room = 0; room < roomCount; room++)
		rooms[room] = intlRoomFromFile(filename, layout, p, renderer);

	layout.close();
	rooms[currentRoom]->setDiscovered(true);

	intlGetObjectsFromFile(filename, data, renderer, p);

	data.close();
}

void Map::intlGetObjectsFromFile(string filename, ifstream& data, RenderContext& renderer, Player& p)
{
	string line3;
	int uniqueId = 0; //This integer is used to make sure the identifier of each objects in the room is unique

	while (getline(data, line3)) //We now add the objects to the rooms
	{
		/*For each object, we extract its position in the map, its identifier,
		and the rest of the information needed to construct the object and add
		it to the map*/
		if (line3[line3.length() - 1] == '\r')
		{
			line3.erase(line3.length() - 1);
		}
		int room, x, y;
		size_t a;
		room = stoi(line3, &a);
		line3.erase(0, a);
		x = stoi(line3, &a);
		line3.erase(0, a);
		y = stoi(line3, &a);
		line3.erase(0, a + 1);
		try
		{
			switch (line3[0])
			{
			case '!':
			{
				rooms[room]->addObject(new Warp(line3, &uniqueId, x, y, renderer));
				break;
			}
			case 'k':
			{
				rooms[room]->addObject(new Key(line3.substr(0, 2), x, y, renderer));
				break;
			}
			case 'd':
			{
				rooms[room]->addObject(new Door(line3, x, y, renderer));
				break;
			}
			case 'c':
			{
				rooms[room]->addObject(new Chest(line3, &uniqueId, x, y, renderer));
				break;
			}
			case 'g':
			{
				Ghost* newGhost = new Ghost(renderer, p, *(rooms[room]));
				newGhost->teleport(x, y);
				rooms[room]->addMonster(newGhost);
				break;
			}
			case 'G':
			{
				IntelligentGhost* newGhost = new IntelligentGhost(renderer, p, *(rooms[room]));
				newGhost->teleport(x, y);
				rooms[room]->addMonster(newGhost);
				break;
			}
			case 's':
			{
				Skeleton* newSkeleton = new Skeleton(renderer, p, *(rooms[room]));
				newSkeleton->teleport(x, y);
				rooms[room]->addMonster(newSkeleton);
				break;
			}
			case 'S':
			{
				IntelligentSkeleton* newSkeleton = new IntelligentSkeleton(renderer, p, *(rooms[room]));
				newSkeleton->teleport(x, y);
				rooms[room]->addMonster(newSkeleton);
				break;
			}
			default:
				cout << "Case " << line3[0] << " not treated yet in " << filename << endl;
				break;
			}
		}
		catch (...)
		{
			cout << "Incomplete header in " << filename << endl;
		}
	}
}

Room* Map::intlRoomFromFile(string filename, ifstream& layout, Player& p, RenderContext& renderer)
{
	string line2;
	Room* thisRoom;/* We determine the dimensions of the room. */
	getline(layout, line2);
	size_t h;
	int width = stoi(line2, &h);
	line2.erase(0, h);
	int height = stoi(line2);
	getline(layout, line2);
	int x = stoi(line2, &h);
	line2.erase(0, h);
	int y = stoi(line2);
	thisRoom = new Room(width, height, x, y, p, renderer);

	for (int i = 0; i < height; i++)
	{
		getline(layout, line2);
		for (int j = 0; j < width; j++) {
			switch (line2[j])
			{
			case ' ':
				break;
			case 'w':
				thisRoom->replaceBlock(new WallBlock(j, i, renderer));
				break;
			case 'g':
				thisRoom->replaceBlock(new FloorBlock(j, i, renderer, "grass"));
				break;
			case 'b':
				thisRoom->replaceBlock(new FloorBlock(j, i, renderer, "bush"));
				break;
			case 't':
				thisRoom->replaceBlock(new WallBlock(j, i, renderer, "tree"));
				break;
			case 'f':
				thisRoom->replaceBlock(new FloorBlock(j, i, renderer));
				break;
			case 's':
				thisRoom->replaceBlock(new StoneWallBlock(j, i, renderer));
				break;
			default:
				cout << "Case " << line2[j] << " not treated yet in " << filename << endl;
				break;
			}
		}
	}
	return thisRoom;
}

