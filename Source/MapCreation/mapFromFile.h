/*#ifndef MAPFROMFILE_H
#define MAPFROMFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include "../Objects/Object.h"
#include "../Objects/Warp.h"
#include "../Maps/Map.h"
#include "../Blocks/Block.h"
#include "../Blocks/WallBlock.h"
#include "../Blocks/FloorBlock.h"
#include "../Blocks/StoneWallBlock.h"

class Warp;

//This function transforms a text file into a folder of texts files which are sufficient to describe the map completely and to be able to modify the maps to save progress. It will create, for each of the maps in the world, a file corresponding to the layout of the map as well as a file containing the objects and monsters that are in the map (and their characteristics, these can change throughout the game, we will therefore modify these files to save progress)

void worldFromFile(string location, string filename, string ext);

//This function turns a folder of files representing a world and returns the current map. destMap, destRoom, destX and destY correspond to the destination coordinates, i.e. where the player starts. When they are different from -1, the player is warping from one map to another, and when they are equal to -1 we must read them in the Start file.

Map* mapFromFiles(string filename, string ext, Player& p, RenderContext& renderer, int startMap = -1, int startRoom = -1);

#endif*/
