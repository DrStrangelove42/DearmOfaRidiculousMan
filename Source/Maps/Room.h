#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "../Base/Entity.h"
#include "../Base/game.h"
#include "../Base/utils.h"
#include "../Blocks/FloorBlock.h"
#include "../Blocks/Block.h"
#include "../Objects/Object.h"
#include <unordered_map>
#include <list>
#include "../Characters/Monster.h"

using namespace std;

class Map;

class Room : public Entity
{
protected:
	/// <summary>
	/// Width of the room, in blocks.
	/// </summary>
	int w;
	
	/// <summary>
	/// Height of the room, in blocks.
	/// </summary>
	int h;
	
	/// <summary>
	/// X coordinate of the absolute location of the first block (top-left corner, blocks[0][0]) of this room in the map, in blocks.
	/// </summary>
	int x;
	
	/// <summary>
	/// Y coordinate of the absolute location of the first block (top-left corner, blocks[0][0]) of this room in the map, in blocks.
	/// </summary>
	int y;

	/// <summary>
	/// A reference to the player.
	/// </summary>
	Player& player;

	/// <summary>
	/// A matrix of size <code>w</code> times <code>h</code> of references to blocks, which are the basic compound of a room.
	/// </summary>
	Block*** blocks;

	/// <summary>
	/// A boolean indicating whether the room has already been visited by the player. We will only show on screen the rooms that have been discovered.
	/// </summary>
	bool discovered;
	
	/// <summary>
	/// The unordered map of objects in the room.
	/// </summary>
	unordered_map <string, Object*> objects;

	/// <summary>
	/// The list of monsters in the room.
	/// </summary>
	list<Monster*> monsters;

	/// <summary>
	/// A list of monsters that need deleting from the room.
	/// </summary>
	list<Monster*> pendingToRemove;

	int lastCleaned = 0;
	int cleanDelay = 10000;

	bool breakObjectUpdateLoop;
public:
	/* Creates a new Room object */
	Room(int width, int height, int absx, int absy, Player& p, RenderContext& renderer);

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	bool isTraversable(int, int);
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="m"></param>
	void addMonster(Monster* m);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="m"></param>
	void removeMonster(Monster* m);

	void removeObject(string id);

	/* Standard destructor */
	virtual ~Room();

	/// <summary>
	/// Adds an object to the room.
	/// </summary>
	/// <param name="object"></param>
	void addObject(Object* object);

	/// <summary>
	/// Tells the room that it must stop scanning through objects (e.g. when a warp changes the room).
	/// </summary>
	void stopScanningObjects();

	/// <summary>
	/// Asks to move the entity on the room
	/// </summary>
	/// <param name="e"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void tryTeleportAt(MovingEntity& e, int x, int y);

	/// <summary>
	/// Updates all objects in the room accordingly.
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	void tick(int time, GAME* game);

	/// <summary>
	/// Updates all monsters in the room accordingly.
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	void updateAllMonsters(int time, GAME* game);

	/// <summary>
	/// Rendering method, enabling the renderer to take the offset (in blocks) into account.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)const;

	/// <summary>
	/// Changes a block in the room, according to its location
	/// </summary>
	/// <param name="newBlock"></param>
	void replaceBlock(Block* newBlock);

	/// <summary>
	/// When a key is pushed on the keyboard.
	/// </summary>
	/// <param name="ea"></param>
	virtual void onKeyDown(GAME* game);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Block* getCurrentBlock();

	/* In case of copy-assignment use */
	/*Room& operator=(const Room& that)
	{
		if (this != &that)
		{
			w = that.w;
			h = that.h;
			player = that.player;

			if (w > 0 && h > 0)
			{
				blocks = new Block ** [w];
				for (int i = 0; i < w; i++)
				{
					blocks[i] = new Block*[h];

					for (int j = 0; j < h; j++)
					{
						blocks[i][j] = that.blocks[i][j];
					}
				}
			}
		}
		return *this;
	}*/

	/* Accessors */
	int getW()const;
	int getH()const;
	int getX()const;
	int getY()const;
	Block*** getBlocks();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	list<Monster*>& getMonsters();

	unordered_map <string, Object*>& getObjects();

	/* Setters */
	void setDiscovered(bool b);

	/// <summary>
	/// Removes dead monsters.
	/// </summary>
	void cleanMonsters();

	/// <summary>
	/// Adds the warp information to each of the intelligent monsters in the room.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="destRoom"></param>
	/// <param name="destX"></param>
	/// <param name="destY"></param>
	/// <param name="playerJustLeft"></param>
	void sendMonstersToWarp(int x, int y, int destRoom, int destX, int destY, bool playerJustLeft);

	/// <summary>
	/// Empties the intelligent monsters in the room of their <code>warpInfo</code>: this is for when the monsters are in the same room as the player and so they no longer need to go towards a warp. The information needs to be cleaned to prepare for the next time that the player warps.
	/// </summary>
	void cleanMonsterWarpInfo();

	void addMonsterToRemove(Monster* m);
};


#endif
