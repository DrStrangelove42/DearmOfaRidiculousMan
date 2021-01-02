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

class Room : public Entity
{
protected:
	/* Dimensions of the room, in blocks */
	int w;
	int h;
	/* Absolute location of the first block (top-left corner, blocks[0][0])
	   of this room in the map, in blocks unit */
	int x;
	int y;

	/* The player currently in the room */
	Player& player;
	/* The blocks are the basic compound of a room */
	Block*** blocks;
	/* If the room has already been visited */
	bool discovered;
	/* The unordered map of objects in the room.*/
	unordered_map <string, Object*> objects;

	list<Monster*> monsters;

	int lastCleaned = 0;
	int cleanDelay = 10000;
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
	/// Asks to move the entity on the room
	/// </summary>
	/// <param name="e"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void tryTeleportAt(MovingEntity& e, int x, int y);

	/// <summary>
	/// Updates all objects in the room accordingly.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="ea"></param>
	void updateAllObjects(GAME* game);

	/// <summary>
	/// Rendering method, enabling the renderer to take the offset (in blocks) into account.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)const;

	/// <summary>
	/// Time management
	/// </summary>
	/// <param name="time"></param>
	/// <param name="r"></param>
	virtual void tick(int time, GAME* game);

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
};


#endif
