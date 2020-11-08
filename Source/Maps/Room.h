#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "../Base/Entity.h"
#include "../Blocks/FloorBlock.h"
#include "../Blocks/Block.h"
#include <SDL2/SDL.h>

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

public:
	/* Creates a new Room object */
	Room(int width, int height, Player& p, RenderContext& renderer);

	/* Standard destructor */
	virtual ~Room();

	/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);

	/* Time management */
	virtual void tick(int time);

	/* Changes a block in the room, according to its location */
	void replaceBlock(Block* newBlock);

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
	int getW();
	int getH();
	int getX();
	int getY();
};


#endif
