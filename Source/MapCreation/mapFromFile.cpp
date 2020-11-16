#include "mapFromFile.h"

void worldFromFile(string filename, string ext) {
	int NumberOfMaps, NumberOfRooms, height, width;
	string line;
	string newFile = filename.append("/").append(filename); //A string we will use often
	ifstream World(filename.append(ext));

	getline(World, line);
	NumberOfMaps = stoi(line);

	string descriptions = "";
	int headerLength = 0;

	getline(World, line);

	while (line != "###") {
		if (line != "") {
			descriptions += line + "\n";
			headerLength += 1;
		}
		getline(World, line);
	}

	string* header = new string[headerLength]; //This array will contain each non-empty line (except the first one which contains the number of maps) before the first ## in the file, that is to say all the additional information needed to describe objects and entities (or anything else that is added), such as contents of chests, characteristics of monsters, that are i the world.

	for (int i = 0; i < headerLength; i++) {
		int firstlineskip = descriptions.find("\n");
		header[i] = descriptions.substr(0, firstlineskip);
		descriptions.erase(0, firstlineskip + 1);
	}
	ofstream start(newFile.append("Start").append(ext)); //We create a new file in which we will detail the start position and characteristics of the player
	for (int map = 0; map < NumberOfMaps; map++) {
		ofstream layout(newFile.append(to_string(map)).append(ext));
		ofstream data(newFile.append(to_string(map)).append("Data").append(ext));
		getline(World, line);
		if (line != "##") {
			cout << "Expected ## before beginning of map " << map << endl;
		}
		getline(World, line);
		NumberOfRooms = stoi(line);
		layout << to_string(NumberOfRooms) << endl;
		for (int room = 0; room < NumberOfRooms; room++) {
			getline(World, line);
			if (line != "#") {
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

			for (int i = 0; i < height; i++) {
				getline(World, line);
				string extraspaces = string(width * 3 - line.length(), ' ');
				line += extraspaces; //We add extra spaces so that all lines in the file are of the same length : width*3. If we find an empty space, it is an empty block. 
				for (int j = 0; j < width; j++) {
					layout << line[3 * j];
					switch (line[3 * j + 1])
					{
					case ' ':
						break;
					case 'p':
						start << to_string(map) << " " << to_string(room) << " " << to_string(i) << " " << to_string(j) << endl;
						for (int k = 0; k < headerLength; k++) { //There may be information in the header as to what health or items the player starts with for example
							if (header[k][0] == 'p') {
								start << header[k].erase(0);
							}
						}
						start.close();
						break;
					default:
						for (int k = 0; k < headerLength; k++) {
							if (header[k][0] == line[3 * j + 1] && header[k][1] == line[3 * j + 2]) {
								data << to_string(room) << " " << to_string(j) << " " << to_string(i) << " " << header[k] << endl;
								break;
							}
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

Map* mapFromFiles(string filename, string ext, Player& p, RenderContext& renderer, int startMap, int startRoom, int startX, int startY)
{
	ifstream start(filename.append("Start").append(ext));
	string line1, line2, line3;
	size_t a;
	int startMap2, startRoom2, startX2, startY2;
	if (startMap == -1)
	{
		getline(start, line1);
		startMap2 = stoi(line1, &a);
		line1.erase(0, a);
	}
	else
	{
		startMap2 = startMap;
	}

	ifstream layout(filename.append(to_string(startMap2)).append(ext));
	ifstream data(filename.append(to_string(startMap2)).append("Data").append(ext));

	getline(layout, line2);
	int NumberOfRooms = stoi(line2);
	Map* currentMap = new Map(p, NumberOfRooms);
	for (int room = 0; room < NumberOfRooms; room++)
	{
		getline(layout, line2);
		if (line2 != "#")
		{
			cout << "Expected # before beginning of room " << room << endl;
			return currentMap;
		}

		/* We determine the dimensions of the room. */
		getline(layout, line2);
		size_t h;
		int width = stoi(line2, &h);
		line2.erase(h);
		int height = stoi(line2);

		Room* currentRoom = new Room(width, height, p, renderer);
		for (int i = 0; i < height; i++)
		{
			getline(layout, line2);
			for (int j = 0; j < width; j++) {
				switch (line2[j])
				{
				case ' ':
					break;
				case 'w':
					currentRoom->replaceBlock(new WallBlock(j, i, renderer));
					break;
				case 'f':
					currentRoom->replaceBlock(new FloorBlock(j, i, renderer));
					break;
				case 's':
					currentRoom->replaceBlock(new StoneWallBlock(j, i, renderer));
					break;
				default:
					cout << "Case " << line2[j] << " not treated yet." << endl;
					break;
				}
			}
		}
		currentMap->getRooms()[room] = currentRoom;
	}
	layout.close();

	while (getline(data, line3)) //We now add the objects to the rooms
	{
		//For each object, we extract its position in the map, its identifier, and the rest of the information needed to construct the object and add it to the map
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
			currentMap->getRooms()[room]->addObject(Warp(destMap, destRoom, destX, destY, x, y, id, filename, ext, p, renderer));
			break;
		}
		case 'k':
			//TODO key case. Key identifier is line[3*j+2]
			cout << "Key case not treated yet." << endl;
			break;
		case 'd':
			//TODO door case. Door identifier is line[3*j+2]
			cout << "Door case not treated yet." << endl;
			break;

			//Chests and monsters should be added to the file of mutable elements

		case 'm':
			//TODO monster case. Monster identifier is given by line[3*j+2]
			cout << "Monster case not treated yet." << endl;
			break;
		case 'c':
			//TODO chest case. Chest identifier is given by line[3*j+2]
			cout << "Chest case not treated yet." << endl;
			break;
		default:
			cout << "Case " << line3[0] << " not treated yet." << endl;
			break;
		}
	}
	data.close();
	if (startRoom == -1)
	{
		startRoom2 = stoi(line1, &a);
		line1.erase(0, a);
		startX2 = stoi(line1, &a);
		line1.erase(0, a);
		startY2 = stoi(line1);
	}
	else
	{
		startRoom2 = startRoom;
		startX2 = startX;
		startY2 = startY;
	}
	currentMap->currentRoom = startRoom2;
	p.teleport(startX2, startY2);
	//TODO other player characteristics
	start.close();
	return currentMap;
}
