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
	/* The player currently in the room */
	Player &player;
	/* The blocks are the basic compound of a room */
	Block *** blocks;
	

public:
	/* Creates a new Room object */
	Room(int width, int height, Player& p, SDL_Renderer *renderer);
	/* Standard destructor */
	virtual ~Room();
	/* Rendering method */
	virtual void render(SDL_Renderer * renderer);
	/* Time management */
	virtual void tick(int time);

	/* In case of copy-assignment use */
	Room& operator=(const Room& that)
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
	}

	/* Accessors */
	int getW();
	int getH();
};


#endif
