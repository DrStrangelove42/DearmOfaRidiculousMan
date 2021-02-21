#ifndef MAP_H
#define MAP_H

#include "Room.h"
#include "../Base/config.h"
#include "../Base/Entity.h"
#include "../Base/game.h"
#include "../Base/Texture.h"
#include "../Base/utils.h"
#include "../Characters/Butler.h" 
#include "../Characters/Player.h"
#include "../Characters/Monsters/Ghost.h"
#include "../Characters/Monsters/Fireball.h"
#include "../Characters/Monsters/Skeleton.h"
#include "../Characters/Monsters/IntelligentGhost.h"
#include "../Characters/Monsters/IntelligentSkeleton.h"
#include "../Characters/Monsters/IntelligentPet.h"
#include "../Objects/Object.h"
#include "../Objects/Checkpoint.h"
#include "../Objects/Chest.h"
#include "../Objects/Door.h"
#include "../Objects/Key.h"
#include "../Objects/Shield.h"
#include "../Objects/Sword.h"
#include "../Objects/Warp.h"
#include "../Maps/Map.h"
#include "../Blocks/Block.h"
#include "../Blocks/WallBlock.h"
#include "../Blocks/FloorBlock.h"
#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unordered_map>

#ifdef WIN 
#include <direct.h>
#define mkdir(a,b) (_mkdir(a))
#endif

class Map;

/// <summary>
/// A Map is a structure composed of <see cref="Room">Rooms</see>.
/// </summary>
class Map : public Entity
{
protected:
	/// <summary>
	/// Player's starting position in the Map.
	/// </summary>
	int startx, starty;
	
	/// <summary>
	/// Mouse-Event handlers.
	/// </summary>
	unordered_map<DrawableEntity*, function<void(MOUSE_DATA*)>> mouseEventHandlers;

	/// <summary>
	/// Allows to exit a loop when a Button for example destructs the Map object.
	/// </summary>
	bool deleting;

	/// <summary>
	/// Array of pointers to <see cref="Room">Rooms</see>.
	/// </summary>
	Room** rooms;

	/// <summary>
	/// Reference to the Player.
	/// </summary>
	Player& player;

	/// <summary>
	/// Number of <see cref="Room">Rooms</see> in the Map.
	/// </summary>
	int roomCount;

	/// <summary>
	/// Index of the Room that is currently displayed (in which the Player is)
	/// </summary>
	int currentRoom;

	/// <summary>
	/// The name of the current world to which this map belongs.
	/// </summary>
	string worldName;

	/// <summary>
	/// The name (human readable) of this map.
	/// </summary>
	string mapName;

	/// <summary>
	/// Texture of the name of the Map, to be used when necessary.
	/// </summary>
	AnimatedTexture* titleTexture;

	/// <summary>
	/// This function takes a folder of files representing a World (according to the encoding described in HowItWorks.txt) and creates the current Map.
	/// destMap, destRoom, destX and destY correspond to the destination coordinates, i.e. where
	///	the Player starts. When they are different from -1, the Player is <see cref="Warp">warping</see> from one Map to
	///	another, and when they are equal to -1 we must read them in the Start file.
	/// </summary>
	/// <param name="worldName"></param>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="startMap"></param>
	/// <param name="startRoom"></param>
	void mapFromFiles(string worldName, Player& p, RenderContext& renderer, int* startMap, int startRoom);

	/// <summary>
	/// Extracts the data (<see cref="Object">Objects</see> and <see cref="Monster">Monsters</see>) from the ifstream data and adds them to the Map.
	/// </summary>
	/// <param name="worldName"></param>
	/// <param name="data"></param>
	/// <param name="renderer"></param>
	/// <param name="p"></param>
	void intlGetDataFromFile(string worldName, ifstream& data, RenderContext& renderer, Player& p);

	/// <summary>
	/// Here line encodes a Monster or an Object, and they should be treated differently, so we analyse the line to deduce the type of data and call the corresponding function to create it.
	/// </summary>
	/// <param name="line"></param>
	/// <param name="filename"></param>
	/// <param name="renderer"></param>
	/// <param name="uniqueId"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="p"></param>
	/// <param name="room"></param>
	void parseObjectOrMonster(string& line, string& filename, RenderContext& renderer, int* uniqueId, int x, int y, Player& p, int room);

	/// <summary>
	/// Creates the Room thanks to the layout file, by creating a Room of the correct shape and in the correct position, and then replacing each Block with the correct one.
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="layout"></param>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <returns></returns>
	Room* intlRoomFromFile(string filename, ifstream& layout, Player& p, RenderContext& renderer);

	/// <summary>
	/// Parses the Map to create the layout and data files, as well as completing the start file if the Player's starting position is in this Map.
	/// </summary>
	/// <param name="newFile"></param>
	/// <param name="map"></param>
	/// <param name="World"></param>
	/// <param name="start"></param>
	/// <returns></returns>
	static bool intlParseMap(string& newFile, int map, ifstream& World, ofstream& start);

	/// <summary>
	/// Parses the Room to add to the layout and data files for that Room, as wall as completing the start file if the Player's starting position is in this Room.
	/// </summary>
	/// <param name="newFile"></param>
	/// <param name="World"></param>
	/// <param name="map"></param>
	/// <param name="room"></param>
	/// <param name="layout"></param>
	/// <param name="start"></param>
	/// <param name="data"></param>
	/// <returns></returns>
	static bool intlParseRoom(string& newFile, ifstream& World, int map, int room, ofstream& layout, ofstream& start, ofstream& data);
	
public:
	/// <summary>
	/// Parses the string line to create the corresponding Object.
	/// </summary>
	/// <param name="line"></param>
	/// <param name="renderer"></param>
	/// <param name="uniqueId"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static Object* parseObject(string& line, RenderContext& renderer, int* uniqueId, int x, int y);

	/// <summary>
	/// Parses the string line to create the corresponding Monster.
	/// </summary>
	/// <param name="line"></param>
	/// <param name="renderer"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	static Monster* parseMonster(string& line, RenderContext& renderer, int x, int y, Player& p, Room* r);
	
	/// <summary>
	/// This function transforms a text file into a folder of texts files which are sufficient 
	/// to describe the Map completely and to be able to modify the <see cref="Map">Maps</see> to save progress.
	///	It will create, for each of the <see cref="Map">Maps</see> in the world, a file corresponding to the layout
	///	of the Map as well as a file containing the <see cref="Object">Objects</see> and <see cref="Monster">Monsters</see> that are in the Map
	///	(and their characteristics, these can change throughout the game, we will therefore
	/// modify these files to save progress).
	/// </summary>
	/// <param name="worldName"></param>
	static void worldFromFile(string worldName);

	/// <summary>
	/// Creates a new empty Map with a pre-allocated array for <see cref="Room">Rooms</see>.
	/// </summary>
	/// <param name="p"></param>
	/// <param name="roomCount"></param>
	Map(Player& p, int roomCount, RenderContext& r);

	/// <summary>
	/// Creates a Map object from a Map file. Either it is the initial creation of the Map, 
	/// in which case *startMap is worth -1 and the initial Map, Room and position must be read in 
	/// the start file, or it is a Warp to an external Map, in which case startMap and startRoom are specified.
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="p"></param>
	/// <param name="renderer"></param>
	/// <param name="startMap"></param>
	/// <param name="startRoom"></param>
	Map(string filename, Player& p, RenderContext& renderer, int* startMap, int startRoom = -1);

	/// <summary>
	/// Destructor. 
	/// </summary>
	virtual ~Map();

	/// <summary>
	/// Saves the Player's progress in a folder, so that the game can be resumed at a later date.
	/// </summary>
	/// <param name="saveName"></param>
	/// <param name="originalWorldName"></param>
	/// <param name="mapNumber"></param>
	/// <param name="roomNumber"></param>
	/// <returns></returns>
	void saveProgress(string saveName, string originalWorldName, int mapNumber, int roomNumber, Player& p);

	/// <summary>
	/// <see cref="RenderContext">Rendering</see> method, enabling the <see cref="RenderContext::renderer">renderer</see> to take the offset (in <see cref="Block">blocks</see>) into account.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0) const;

	/// <summary>
	/// Time management.
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	virtual void tick(int time, GAME* game);

	/// <summary>
	/// Event system.
	/// </summary>
	/// <param name="game"></param>
	virtual void onKeyDown(GAME* game);

	/// <summary>
	/// <see cref="MOUSE_DATA">Mouse event</see>.
	/// </summary>
	/// <param name="md"></param>
	virtual void onMouseEvent(MOUSE_DATA* md);

	/* Setter. */
	void setCurrentRoom(int c);

	/* Accessors. */
	int getRoomCount();
	Room** getRooms();
	int getCurrentRoom();
	Room& getCurrentRoomObject();

	/// <summary>
	/// Adds a callback to call on receiving a <see cref="MOUSE_DATA">mouse event</see>.
	/// </summary>
	/// <param name="callback"></param>
	void addMouseHandler(DrawableEntity* entity, function<void(MOUSE_DATA*)> callback);

	/// <summary>
	/// Removes a handler from the list.
	/// </summary>
	/// <param name="entity"></param>
	void removeMouseHandler(DrawableEntity* entity);

	/// <summary>
	/// Teleports the Player to the starting position.
	/// </summary>
	void teleportPlayerOnStart();

	/// <summary>
	/// Adds the Warp information to each IntelligentMonster in the Map.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="destRoom"></param>
	/// <param name="destX"></param>
	/// <param name="destY"></param>
	void sendMonstersToWarp(int x, int y, int destRoom, int destX, int destY);

	/// <summary>
	/// Called when the map is loaded to the screen.
	/// </summary>
	virtual void onEnter();
};

#endif
