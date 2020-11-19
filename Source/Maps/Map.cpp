#include "Map.h"

Map::Map(Player& p, int roomCount) : player(p), roomCount(roomCount), currentRoom(0)
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

Map::Map(string filename, Player& p, RenderContext& renderer, int* startMap, int startRoom) : player(p)
{
	mapFromFiles(filename, p, renderer, startMap, startRoom);
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
}

void Map::tick(int time, RenderContext& r)
{
	rooms[currentRoom]->tick(time, r);
}

Room** Map::getRooms()
{
	return rooms;
}

int Map::getCurrentRoom()
{
	return currentRoom;
}

void Map::onKeyDown(EVENT_ARGS* ea)
{
	rooms[currentRoom]->onKeyDown(ea);
}

void Map::worldFromFile(string location, string filename) {
	int NumberOfMaps, NumberOfRooms, height, width;
	string line;
	string newFile = location + filename + "/" + filename; //A string we will use often
	ifstream World(location + filename + WORLDFILE_EXT);

	getline(World, line);
	NumberOfMaps = stoi(line);

	ofstream start(newFile + "Start" + WORLDFILE_EXT); //We create a new file in which we will detail the start position and characteristics of the player
	for (int map = 0; map < NumberOfMaps; map++) {
		ofstream layout(newFile + to_string(map) + WORLDFILE_EXT);
		ofstream data(newFile + to_string(map) + "Data" + WORLDFILE_EXT);
		getline(World, line);
		if (line.length() == 0 || line[0] != '#') {
			cout << "Expected ## before beginning of map " << map << endl;
		}
		getline(World, line);
		NumberOfRooms = stoi(line);
		layout << to_string(NumberOfRooms) << endl;

		for (int room = 0; room < NumberOfRooms; room++) {

			getline(World, line);
			if (line.length() == 0 || line[0] != '#')
			{
				cout << "Expected # before beginning of room " << room << endl;
				return;
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

			while (line.length() == 0 || line[0] != '#') {
				if (line != "")
				{
					descriptions += line + "\n";
					headerLength += 1;
				}
				getline(World, line);
			}

			string* header = new string[headerLength];

			//This array will contain each non-empty line between the absolute position of the room and the next line starting with #, that is to say all the additional information needed to describe objects and entities (or anything else that is added), such as contents of chests, characteristics of monsters, that are in the room.

			for (int i = 0; i < headerLength; i++)
			{
				int firstlineskip = descriptions.find("\n");
				header[i] = descriptions.substr(0, firstlineskip);
				descriptions.erase(0, firstlineskip + 1);
			}

			for (int i = 0; i < height; i++) {
				getline(World, line);
				if (line[line.length() - 1] == '\r')
				{
					line.erase(line.length() - 1);
				}
				string extraspaces = string(max(0, width * 3 - int(line.length())), ' ');
				line += extraspaces; //We add extra spaces so that all lines in the file are of the same length : width*3. If we find an empty space, it is an empty block.
				for (int j = 0; j < width; j++) {
					layout << line[3 * j];
					switch (line[3 * j + 1])
					{
					case ' ':
						break;
					case 'p':
						start << to_string(map) << " " << to_string(room) << " " << to_string(j) << " " << to_string(i) << endl;
						for (int k = 0; k < headerLength; k++) { //There may be information in the header as to what health or items the player starts with for example
							if (header[k][0] == 'p') {
								start << header[k].erase(0);
							}
						}
						start.close();
						break;
					default:
						data << to_string(room) << " " << to_string(j) << " " << to_string(i) << " ";
						bool notinheader = true;
						for (int k = 0; k < headerLength; k++) {
							if (header[k][0] == line[3 * j + 1] && header[k][1] == line[3 * j + 2]) {
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
		}
		layout.close();
		data.close();

	}
	World.close();
	return;
}

void Map::mapFromFiles(string filename, Player& p, RenderContext& renderer, int* startMap, int startRoom)
{
	ifstream start(filename + "Start" + WORLDFILE_EXT);
	string line1, line2, line3;
	size_t a;
	int startX, startY;

	if (*startMap == -1)
	{
		getline(start, line1);
		*startMap = stoi(line1, &a);
		line1.erase(0, a);
		startRoom = stoi(line1, &a);
		line1.erase(0, a);
		startX = stoi(line1, &a);
		line1.erase(0, a);
		startY = stoi(line1);
		player.teleport(startX, startY);
	}
	//TODO other player characteristics
	start.close();
	ifstream layout(filename + to_string(*startMap) + WORLDFILE_EXT);
	ifstream data(filename + to_string(*startMap) + "Data" + WORLDFILE_EXT);

	getline(layout, line2);
	roomCount = stoi(line2);

	rooms = new Room * [roomCount];
	currentRoom = startRoom;
	Room* thisRoom;
	for (int room = 0; room < roomCount; room++)
	{
		/* We determine the dimensions of the room. */
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
				case 'f':
					thisRoom->replaceBlock(new FloorBlock(j, i, renderer));
					break;
				case 's':
					thisRoom->replaceBlock(new StoneWallBlock(j, i, renderer));
					break;
				default:
					cout << "Case " << line2[j] << " not treated yet." << endl;
					break;
				}
			}
		}
		rooms[room] = thisRoom;
	}
	layout.close();
	rooms[currentRoom]->setDiscovered(true);

	while (getline(data, line3)) //We now add the objects to the rooms
	{
		//For each object, we extract its position in the map, its identifier, and the rest of the information needed to construct the object and add it to the map
	        int uniqueId = 0; //This integer is used to make sure the identifier of each objects in the room is unique
		int room, x, y;
		size_t a;
		room = stoi(line3, &a);
		line3.erase(0, a);
		x = stoi(line3, &a);
		line3.erase(0, a);
		y = stoi(line3, &a);
		line3.erase(0, a + 1);
		switch (line3[0])
		{
		case '!':
		{
			string id = line3.substr(0, 2);
			line3.erase(0, 2);
			int destMap = stoi(line3, &a);
			line3.erase(0, a);
			int destRoom = stoi(line3, &a);
			line3.erase(0, a);
			int destX = stoi(line3, &a);
			line3.erase(0, a);
			int destY = stoi(line3);
			rooms[room]->addObject(new Warp(destMap, destRoom, destX, destY, x, y, id, p, renderer));
			break;
		}
		case 'k':
		{
			string id = line3.substr(0, 2);
			rooms[room]->addObject(new Key(id, x, y, p, renderer));
			break;
		}
		case 'd':
		{
			string id = line3.substr(0, 6);
			rooms[room]->addObject(new Door(id, x, y, p, renderer));
			break;
		}
		case 'c':
		{
			string id = line3.substr(0, 2);
			line3.erase(0,3);
			Chest* newChest = new Chest(id, x, y, p, renderer);
			while (line3.length()>=2)
			{
			        switch(line3.substr(0,2))
			        {
				case "sw"
				        newChest.addItem(Sword("sw"+to_string(uniqueId++), renderer));
				break;
				case "sh"
				        newChest.addItem(Shield("sh"+to_string(uniqueId++), renderer));
				  break;
				}
				line3.erase(0,2);
				if (line3.length>0)
				{
				      line3.erase(0,1);
				}
			}
			rooms[room]->addObject(newchest);
			break;
		}
		case 'g':
		  rooms[room]->addMonster(new Ghost(renderer,p));
		  break;
		case 's':
		  rooms[room]->addMonster(new Skeleton(renderer,p));
		  break;
		default:
			cout << "Case " << line3[0] << " not treated yet." << endl;
			break;
		}
	}
	data.close();
	return;
}
