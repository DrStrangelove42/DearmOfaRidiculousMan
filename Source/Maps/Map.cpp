#include "Map.h"

Map::Map(Player& p, int roomCount, RenderContext& r) :
	player(p), roomCount(roomCount), currentRoom(0), titleTexture(NULL), deleting(false), startx(2), starty(2), mapName("Manually generated map")
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

	mouseEventHandlers.clear();

	topMostTextures.clear();

	deleting = true;
}

Map::Map(string worldName, Player& p, RenderContext& renderer, int* startMap, int startRoom) :
	player(p), worldName(worldName), currentRoom(0), roomCount(0), titleTexture(NULL), rooms(NULL), deleting(false), startx(2), starty(2), mapName("")
{
	// First we determine whether the files representing the world need to be generated, that is to say whether these files don't exist or whether they are older than the file representing the world.
	struct stat dataLocation;
	struct stat world;
	struct stat data;

	if (stat(WORLDDATA_LOCATION.c_str(), &dataLocation) != 0)
	{
		string d = DATA_LOCATION + "Data/";
		if (mkdir(d.c_str(), 0777) != 0)
		{
			cout << "MKDIR DATA failed" << endl;
			cout << " with " << WORLDDATA_LOCATION << endl;
			return;
		}
		if (mkdir(WORLDDATA_LOCATION.c_str(), 0777) != 0)
		{
			cout << "MKDIR " << WORLDDATA_LOCATION << " failed" << endl;
			return;
		}
	}

	if (stat((WORLDFILES_LOCATION + worldName + EXT).c_str(), &world) != 0)
	{
		cout << WORLDFILES_LOCATION + worldName + EXT << " doesn't exist..." << endl;
		return;
	}

	if (stat((WORLDDATA_LOCATION + worldName + "/" + worldName + "Start" + EXT).c_str(), &data) != 0)
	{
		if (mkdir((WORLDDATA_LOCATION + worldName + "/").c_str(), 0777) != 0)
		{
			cout << "MKDIR " << WORLDDATA_LOCATION + worldName << " failed" << endl;
			return;
		}
		worldFromFile(worldName);
	}
	else
	{
		auto worldTime = world.st_mtime;
		auto dataTime = data.st_mtime;
		if (dataTime < worldTime)	//Update world file if the map file is newer
			worldFromFile(worldName);
	}
	mapFromFiles(worldName, p, renderer, startMap, startRoom);

	list<int> fg = CreateFade(0xFFFFFFFF, 0xFFFFFF00, 10, 40);
	list<int> bg = CreateFade(0x000000FF, 0x00000000, 10, 40);

	titleTexture = static_cast<AnimatedTexture*>(renderer.LoadAnimatedBoxedString(mapName, fg, bg, 100, false));
}

void Map::render(RenderContext& renderer, int offsetX, int offsetY) const
{
	Room* cur = rooms[currentRoom];

	int offX = offsetX - cur->getX() + (BLOCKS_W - cur->getW()) / 2;
	int offY = offsetY - cur->getY() + (BLOCKS_H - cur->getH()) / 2;
	int i = 0;
	for (; i < currentRoom; i++)
	{
		rooms[i]->render(renderer, offX, offY);
	}
	cur->render(renderer, offX, offY);

	player.render(renderer, offX + cur->getX(), offY + cur->getY());

	for (i++; i < roomCount; i++)
	{
		rooms[i]->render(renderer, offX, offY);
	}

	titleTexture->renderUnscaled(renderer, 3 * SZ_BLOCKSIZE, 3 * SZ_BLOCKSIZE);

	//Render top most textures
	for (auto& entry : topMostTextures)
	{
		entry.second.t->renderUnscaled(renderer, entry.second.x, entry.second.y);
	}

#ifdef DEBUG_MODE

	renderer.LoadString("CURRENT MAP : " + worldName, 0xffffffAA)->renderUnscaled(renderer, 0, 0);
	renderer.LoadString("Room : " + to_string(currentRoom), 0x00FFffAA)->renderUnscaled(renderer, 0, 16);
#endif
}

void Map::tick(int time, GAME* game)
{
	rooms[currentRoom]->tick(time, game);
	for (int i = 0; i < roomCount; i++)
	{
		rooms[i]->updateAllMonsters(time, game);
	}
}

void Map::setCurrentRoom(int c)
{
	currentRoom = c;
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

void Map::addMouseHandler(DrawableEntity* entity, function<void(MOUSE_DATA*)> callback)
{
	mouseEventHandlers[entity] = callback;
}

void Map::removeMouseHandler(DrawableEntity* entity)
{
	if (mouseEventHandlers.find(entity) != mouseEventHandlers.end())
		mouseEventHandlers.erase(entity);
}

void Map::teleportPlayerOnStart()
{
	player.teleport(startx, starty);
}

void Map::onKeyDown(GAME* game)
{
	rooms[currentRoom]->onKeyDown(game);
}

void Map::onMouseEvent(MOUSE_DATA* md)
{
	for (auto& f : mouseEventHandlers)
	{
		if (f.first != NULL)
			f.second(md);
		if (deleting)
			return;
	}
	player.onMouseEvent(md);
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
	if (start.is_open())
	{
		cout << "No initial position found for player in " << worldName << ", setting it to default : map, room, x and y set to 0" << endl;
		start << "0 0 0 0";
		start.close();
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
	//int NumberOfRooms = stoi(line); <-- same behaviour so the expanding of the map format 21/02/2021 is non breaking
	int NumberOfRooms = stoi(EatTokenEx(line));
	string mapName = line;
	layout << to_string(NumberOfRooms) << ' ' << mapName << endl;

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
	int uniqueId = 0; //This integer is used to make sure the identifier of each object in the room is unique
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
				if (start.is_open())
				{
					start << to_string(map) << " " << to_string(room) << " " << to_string(j) << " " << to_string(i) << endl;
					for (int k = 0; k < headerLength; k++)
					{ //There may be information in the header as to what health or items the player starts with for example
						if (header[k][0] == 'p')
						{
							start << header[k].substr(2); //We remove "p " from the beginning of the line.
							break;
						}
					}
					start.close();
				}
				else
				{
					cout << "Several initial positions for player found." << endl;
				}
				break;
			default:
				data << to_string(room) << " " << to_string(j) << " " << to_string(i) << " ";
				bool notinheader = true;
				for (int k = 0; k < headerLength; k++)
				{
					if (header[k][0] == line[3 * j + 1] && header[k][1] == line[3 * j + 2])
					{
						data << header[k][0] << header[k][1] << uniqueId++ << header[k].substr(2) << endl;
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

	/*
	If startMap contains the value -1, this means that this is the initial warp,
	and so the initial coordinates of the player need to be read in the start file,
	as well as its initial characteristics and inventory.

	Otherwise, startMap and startRoom are already what we need them to be, and the
	teleportation of the player to the correct position in the room is already taken
	care of.
	*/
	if (*startMap == -1)
	{
		getline(start, line);
		*startMap = stoi(line, &a);
		line.erase(0, a);
		startRoom = stoi(line, &a);
		line.erase(0, a);
		startx = stoi(line, &a);
		line.erase(0, a);
		starty = stoi(line);
		player.teleport(startx, starty);

		if (!getline(start, line))
		{
			line = "";
		}
	}

	start.close();
	ifstream layout(filename + to_string(*startMap) + EXT);



	getline(layout, line);
	//roomCount = stoi(line); <-- Non breaking changes (see also worldFromFile)
	roomCount = stoi(EatTokenEx(line));
	mapName = line;
	rooms = new Room * [roomCount];
	currentRoom = startRoom;

	for (int room = 0; room < roomCount; room++)
		rooms[room] = intlRoomFromFile(filename, layout, p, renderer);

	layout.close();
	rooms[currentRoom]->setDiscovered(true);

	intlGetDataFromFile(filename, *startMap, renderer, p);
}

void Map::intlGetDataFromFile(string filename, int mapIndex, RenderContext& renderer, Player& p)
{
	ifstream data(filename + to_string(mapIndex) + "Data" + EXT);

	int uniqueId = 0; // This integer is used to make sure that objects in chests have unique identifiers.

	/*Is there a saved progress?*/
	string savePath = SAVES_LOCATION + SAVES_CURRENT + "/" + worldName + to_string(mapIndex) + "Data" + EXT;
	struct stat l;
	bool fromSave = false;
	if (stat(savePath.c_str(), &l) == 0)
	{
		//Mutable objects are taken from the saved progress, and other objects from original data file.
		fromSave = true;
		ifstream save(savePath);

		/*Note : if there was a non mutable object in this file, it will be loaded.
		Thus there is still possibility to store all types of objects in the save file ; however
		only mutable objects are saved through the saveProgress function.
		*/
		populateRoomFromDataFile(save, p, false, &uniqueId, renderer, filename);

		save.close();
	}

	populateRoomFromDataFile(data, p, fromSave, &uniqueId, renderer, filename);

	data.close();
}

void Map::populateRoomFromDataFile(ifstream& data, Player& p, bool ignoreMutable, int* PuniqueId, RenderContext& renderer, string& fileNameForInfo)
{

	string line3;
	while (getline(data, line3))
	{
		/* For each line, we extract its position in the map, and the rest of the information
		needed to construct the object and add it to the map thanks to another function. */
		if (line3[line3.length() - 1] == '\r')
			line3.erase(line3.length() - 1);

		int room, x, y;
		room = stoi(EatToken(line3));
		x = stoi(EatToken(line3));
		y = stoi(EatToken(line3));

		try
		{
			parseObjectOrMonster(line3, fileNameForInfo, renderer, PuniqueId, x, y, p, room, ignoreMutable);
		}
		catch (...)
		{
			cout << "Incomplete header in " << fileNameForInfo << endl;
		}
	}
}

void Map::parseObjectOrMonster(string& line, string& filename, RenderContext& renderer, int* uniqueId, int x, int y, Player& p, int room, bool ignoreMutable)
{
	string monsters = "GgSsFP"; //add all Monster types
	string objects = "!kdcBbCADZ$"; //add all object types
	if (monsters.find_first_of(line[0]) != monsters.npos)
	{
		if (!ignoreMutable)
			rooms[room]->addMonster(parseMonster(line, renderer, x, y, p, rooms[room]));
	}
	else if (objects.find_first_of(line[0]) != objects.npos)
	{
		Object* o = parseObject(line, renderer, uniqueId, x, y);
		if (!ignoreMutable || !o->isMutable())
			rooms[room]->addObject(o);
	}
	else
		cout << "Case " << line[0] << " not treated yet in " << filename << endl;
}

Object* Map::parseObject(string& line, RenderContext& renderer, int* uniqueId, int x, int y)
{
	switch (line[0])
	{
	case '!':
	{
		return new Warp(line, x, y, renderer);
	}
	case 'k':
	{
		return new Key(line.substr(0, 2), x, y, renderer);
	}
	case 'd':
	{
		return new Door(line, x, y, renderer);
	}
	case 'c':
	{
		return new Chest(line, uniqueId, x, y, renderer);
	}
	case '$':
	{
		return new Coin(line, x, y, renderer);
	}
	case 'B':
	{
		return new Butler(line, x, y, renderer);
	}
	case 'b':
	{
		return new Sign(line, x, y, renderer);
	}
	case 'C':
	{
		return new Checkpoint(line, x, y, renderer);
	}
	case 'A':
	{
		return new Sword(line, x, y, renderer);
	}
	case 'D':
	{
		return new Shield(line, x, y, renderer);
	}
	case 'Z':
	{
		return new Shop(line, uniqueId, x, y, renderer);
	}
	default:
	{
		cout << "Case " << line[0] << " not treated " << endl;
		return NULL;
	}
	}
}

Monster* Map::parseMonster(string& line, RenderContext& renderer, int x, int y, Player& p, Room* r)
{
	switch (line[0])
	{
	case 'g':
	{
		Ghost* newGhost = new Ghost(renderer, p, r);
		newGhost->teleport(x, y);
		try
		{
			newGhost->setHealth(stoi(line.substr(1)));
		}
		catch (...)/*Default health*/
		{
		}
		return newGhost;
	}
	case 'G':
	{
		IntelligentGhost* newIGhost = new IntelligentGhost(renderer, p, r);
		newIGhost->teleport(x, y);
		try
		{
			newIGhost->setHealth(stoi(line.substr(1)));
		}
		catch (...)/*Default health*/
		{
		}
		return newIGhost;
	}
	case 's':
	{
		Skeleton* newSkeleton = new Skeleton(renderer, p, r);
		newSkeleton->teleport(x, y);
		try
		{
			newSkeleton->setHealth(stoi(line.substr(1)));
		}
		catch (...)/*Default health*/
		{
		}
		return newSkeleton;
	}
	case 'S':
	{
		IntelligentSkeleton* newISkeleton = new IntelligentSkeleton(renderer, p, r);
		newISkeleton->teleport(x, y);
		try
		{
			newISkeleton->setHealth(stoi(line.substr(1)));
		}
		catch (...)/*Default health*/
		{
		}
		return newISkeleton;
	}
	case 'F':
	{
		Fireball* newFireball = new Fireball(renderer, p, r);
		newFireball->teleport(x, y);
		try
		{
			newFireball->setHealth(stoi(line.substr(1)));
		}
		catch (...)/*Default health*/
		{
		}
		return newFireball;
	}
	case 'P':
	{
		IntelligentPet* newIPet = new IntelligentPet(renderer, p, r);
		newIPet->teleport(x, y);
		try
		{
			newIPet->setHealth(stoi(line.substr(1)));
		}
		catch (...)/*Default health*/
		{
		}
		return newIPet;
	}
	default:
		return NULL;
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
			case '.':
				thisRoom->getBlocks()[j][i]->setTrav(true);
				break;
			case 'w':
				thisRoom->replaceBlock(new WallBlock(j, i, renderer));
				break;
			case 'g':
				thisRoom->replaceBlock(new FloorBlock(j, i, renderer, "grass"));
				break;
			case '*':
				thisRoom->replaceBlock(new FloorBlock(j, i, renderer, "glass"));
				break;
			case 'H':
				thisRoom->replaceBlock(new FloorBlock(j, i, renderer, "stairsH"));
				break;
			case 'V':
				thisRoom->replaceBlock(new FloorBlock(j, i, renderer, "stairsV"));
				break;
			case 'S':
				thisRoom->replaceBlock(new FloorBlock(j, i, renderer, "sand"));
				break;
			case 'W':
				thisRoom->replaceBlock(new FloorBlock(j, i, renderer, "*water"));
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
				thisRoom->replaceBlock(new WallBlock(j, i, renderer, "stonewall"));
				break;
			default:
				cout << "Case " << line2[j] << " not treated yet in " << filename << endl;
				break;
			}
		}
	}
	return thisRoom;
}

void Map::saveProgress(string saveName, string originalWorldName, int mapNumber, int roomNumber, Player& p)
{
	struct stat l;
	if (stat((SAVES_LOCATION + saveName).c_str(), &l) != 0)
	{
		if (stat(SAVES_LOCATION.c_str(), &l) != 0)
		{
			if (mkdir(SAVES_LOCATION.c_str(), 0777) != 0)
			{
				cout << "MKDIR SAVES ROOT failed" << endl;
				p.logMessage("Failed to save progress.");
				return;
			}
		}

		string d = SAVES_LOCATION + saveName;
		if (mkdir(d.c_str(), 0777) != 0)
		{
			cout << "MKDIR SAVES failed" << endl;
			cout << " with " << d << endl;
			p.logMessage("Failed to save progress.");
			return;
		}
	}

	ofstream SaveData(SAVES_LOCATION + saveName + "/" + originalWorldName + to_string(mapNumber) + "Data" + EXT);

	for (int room = 0; room < roomCount; room++)
	{
		//Objets
		for (auto& entry : rooms[room]->getObjects())
		{
			Object* cur = entry.second;
			if (cur->isMutable())//Save only mutable objects (doors, chests, any PickableObject)
				SaveData << room << " " << cur->getX() << " " << cur->getY() << " " << cur->objectToString() << endl;
		}

		//Monsters
		list<Monster*> monsters = rooms[room]->getMonsters();
		for (Monster* m : monsters)
		{
			string toAdd = m->monsterToString();
			if (toAdd != "")
			{
				SaveData << room << " " << m->getX() << " " << m->getY() << " " << toAdd << endl;
			}
		}
	}

	SaveData.close();

	p.save(saveName);
}

void Map::sendMonstersToWarp(int x, int y, int destRoom, int destX, int destY)
{
	for (int i = 0; i < roomCount; i++)
	{
		rooms[i]->sendMonstersToWarp(x, y, destRoom, destX, destY, currentRoom == i);
	}
	rooms[destRoom]->cleanMonsterWarpInfo();
}

void Map::onEnter()
{
	if (titleTexture != NULL)
		titleTexture->reset();
}

void Map::registerTopMostTexture(string id, Texture* toReg, int x, int y)
{
	topMostTextures[id] = { toReg, x, y };
}

void Map::unregisterTopMostTexture(string id)
{
	if (topMostTextures.find(id) != topMostTextures.end())
		topMostTextures.erase(id);
}

