#include <iostream>
#include <fstream>
#include <string>
#include "../Maps/Map.h"

//This function transforms a text file into a folder of texts files which are sufficient to describe the map completely and to be able to modify the maps to save progress. It will create, for each of the maps in the world, a file corresponding to the layout of the map as well as a file containing the objects and monsters that are in the map (and their characteristics, these can change throughout the game, we will therefore modify these files to save progress)

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
			line.erase(h);
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
							  start << (header[k]).erase(0);
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
