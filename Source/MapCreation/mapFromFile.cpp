#include <iostream>
#include <fstream>
#include <string>
#include "../Maps/Map.h"
#include "../Blocks/WallBlock.h"
#include "../Blocks/FloorBlock.h"
#include "../Blocks/WarpBlock.h"

//This function transforms a text file into the corresponding map files and a file describing the mutables. When a new game is started, the mutable file is applied to the maps to create the default map. When a game is saved, a copy of the mutable file with the appropriate changes is saved, and can then be loaded at a later date by applying the new mutable file to the maps

//TODO the mutable file

void worldFromFile(string filename, string ext, Player& p, RenderContext& renderer){
  int NumberOfMaps, NumberOfRooms, height, width;
  string line;
  ifstream World(filename.append(ext));
  
  getline(World, line);
  NumberOfMaps = stoi(line);

  string descriptions="";
  int headerLength = 0;

  getline(World,line);

  while (line!="###"){
    if (line!=""){
      descriptions+=line+"\n";
      headerLength +=1;
    }
    getline(World,line);
  }

  string *header = new string[headerLength]; //This array will contain each non-empty line (except the first one which contains the number of maps) before the first ## in the file, that is to say all the additional information needed to describe objects and entities (or anything else that is added), such as contents of chests, characteristics of monsters, that are i the world.

  for (int i=0;i<headerLength;i++){
    int firstlineskip = descriptions.find("\n");
    header[i] = descriptions.substr(0,firstlineskip);
    descriptions.erase(0,firstlineskip+1);
  }

  for (int map=0;map<NumberOfMaps;map++){
    getline(World, line);
    if (line != "##"){
      cout << "Expected ## before beginning of map " << map << endl;
    }
    getline(World,line);
    NumberOfRooms = stoi(line);
    Map* currentMap = new Map(p,NumberOfRooms);
    for (int room=0;room<NumberOfRooms;room++){
      getline(World, line);
      if (line != "#"){
	cout << "Expected # before beginning of room " << room << endl;
	return;
      }
      /* We determine the dimensions of the room. */
      getline(World, line);
      size_t h;
      width = stoi(line,&h);
      line.erase(h);
      height = stoi(line);
  
      Room* currentRoom = new Room(width,height,p,renderer);
      for (int i=0;i<height;i++){
	getline(World, line);
	string extraspaces = string(width*3-line.length(),' ');
	line+=extraspaces; //We add extra spaces so that all lines in the file are of the same length : width*3. If we find an empty space, it is an empty block. 
	for (int j=0;j<width;j++){
	  switch (line[3*j])
	    {
	    case ' ':
	      //TODO Empty block (for non rectangular rooms mainly)
	      cout << "Case ' ' not treated yet." <<endl;
	      break;
	    case 'w':
	      currentRoom->replaceBlock(new WallBlock(j,i,p,renderer));
	      break;
	    case 'f':
	      currentRoom->replaceBlock(new FloorBlock(j,i,p,renderer));
	      break;
	    default:
	      cout << "Case " << line[3*j] << " not treated yet." <<endl;
	    }
	  switch (line[3*j+1])
	    {
	    case ' ':
	      break;
	    case 'p':
	      currentMap->currentRoom=room; //This should actually be stored in the mutable file
	      p.teleport(j,i);
	    case '!':
	      for (int k=0;k<headerLength;k++){
		if (header[k][0]=='!' && header[k][1]==line[3*j+2]){
		  string destination = header[k].erase(0,2);
		  size_t roomAndCoord, coords, y;
		  int destMap = stoi(destination,&roomAndCoord);
		  destination.erase(roomAndCoord);
		  int destRoom = stoi(destination,&coords);
		  destination.erase(coords);
		  int destX = stoi(destination,&y);
		  destination.erase(y);
		  int destY = stoi(destination);
		  if (destMap = map){
		    currentRoom->replaceBlock(new WarpBlock(j,i,p,"floor",renderer,destRoom,destX,destY));
		  }
		  {
		    cout << "Warp towards other maps not treated yet." << endl;
		  }
		  break;
		}
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
	      cout << "Case " << line[3*j+1] << " not treated yet." <<endl;
	    }
	}
      }
      currentMap->getRooms()[room] = currentRoom;
    }
    //TODO create map "filename".append(map), a map without the mutables
  }
  World.close();
	  //For each case, when necessary, we should look in descriptions to find the extra information needed for the object/entity. For example, if we find a chest with identifier 1, we search for the first string in descriptions starting with "c1", after which the contents will be encoded.
	  //Furthermore, for certain types of objects, the identifier links that object with another object. For example, if we have !1, that block will warp us to the block that is followed by ?1, if we have k1, that key will unlock doors d1.
  return;
}
