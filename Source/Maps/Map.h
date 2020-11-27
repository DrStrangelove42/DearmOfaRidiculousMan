#ifndef MAP_H
#define MAP_H

#include <string>
#include "Room.h"
#include "../Base/Entity.h"
#include "../Base/config.h"
#include "../Base/game.h"
#include "../Base/utils.h"
#include "../Characters/Player.h"
 
#include <iostream>
#include <fstream>
#include "../Objects/Object.h"
#include "../Objects/Chest.h"
#include "../Objects/Door.h"
#include "../Objects/Key.h"
#include "../Objects/Warp.h"
#include "../Maps/Map.h"
#include "../Blocks/Block.h"
#include "../Blocks/WallBlock.h"
#include "../Blocks/FloorBlock.h"
#include "../Blocks/StoneWallBlock.h"
#include "../Characters/Monsters/Ghost.h"
#include "../Characters/Monsters/Skeleton.h"
#include "../Items/Item.h"
#include "../Items/Shield.h"
#include "../Items/Sword.h"

/*
A map represents a set of rooms displayed one at a time (or one centered
in the view and the others black or greyed).
The initial room is always the first room in the (non empty) array 'rooms'.
*/
class Map : public Entity
{
protected:
	/// <summary>
	/// Array of pointers to rooms
	/// </summary>
	Room ** rooms;
	
	/// <summary>
	/// Reference to the player
	/// </summary>
	Player &player;
	
	/// <summary>
	/// Number of rooms in the map
	/// </summary>
	int roomCount;
	
	/// <summary>
	/// 
	/// </summary>
	string name;

	/// <summary>
	/// 
	/// </summary>
	Texture* titleTexture;
	
	/// <summary>
	/// This function transforms a text file into a folder of texts files which are sufficient 
	/// to describe the map completelyand to be able to modify the maps to save progress.
	///	It will create, for each of the maps in the world, a file corresponding to the layout
	///	of the map as well as a file containing the objectsand monsters that are in the map
	///	(and their characteristics, these can change throughout the game, we will therefore
	/// modify these files to save progress)
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="startMap"></param>
	/// <param name="startRoom"></param>
	void mapFromFiles(string filename, Player& p, RenderContext& renderer, int* startMap, int startRoom);

public:
	/// <summary>
	/// This function turns a folder of files representing a world and returns the current map.
	/// destMap, destRoom, destXand destY correspond to the destination coordinates, i.e.where
	///	the player starts.When they are different from - 1, the player is warping from one map to
	///	another, and when they are equal to - 1 we must read them in the Start file.
	/// </summary>
	/// <param name="location"></param>
	/// <param name="filename"></param>
	static void worldFromFile(string location, string filename);

	/// <summary>
	/// Index of the room that is currently displayed (in which the player is)
	/// </summary>
	int currentRoom;
	/// <summary>
	/// Creates a new empty map with a pre-allocated array for rooms.
	/// </summary>
	/// <param name="p"></param>
	/// <param name="roomCount"></param>
	Map(Player& p, int roomCount);
	
	/// <summary>
	///  Creates a Map object from a map file. Either it is the initial creation of the map, 
	/// in which case *startMap is worth -1 and the initial map, room and position must be read in 
	/// the start file, or it is a warp to an external map, in which case startMap and startRoom are specified.
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="startMap"></param>
	/// <param name="startRoom"></param>
	Map(string filename, Player& p, RenderContext& renderer, int* startMap, int startRoom = -1);

	/* Std destructor */
	virtual ~Map();

	
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */

	
	virtual void tick(int time, GAME* game);/* Time management */

	
	virtual void onKeyDown(GAME* game);/* Event system */

	virtual void onMouseEvent(MOUSE_DATA* md);

	/* Copy-assignment operator */
	/*Map& operator=(const Map& that)
	{
		if (this != &that)
		{
			rooms = new Room*[roomCount];
			for (int i = 0; i < roomCount; i++)
			{
				rooms[i] = that.rooms[i];
			}
			roomCount = that.roomCount;
			currentRoom = that.currentRoom;
			player = that.player;
		}
		return *this;
	}*/
	
	/* Accessors */
	int getRoomCount();
	Room** getRooms();
	int getCurrentRoom();
};

#endif
