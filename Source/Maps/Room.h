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
	Block ** blocks;
	int w;
	int h;
	Player player;

public:
	Room(int width, int height, Player p, SDL_Renderer *renderer);
	~Room();
	void render(SDL_Renderer * renderer);
};


#endif
