#ifndef FLOORBLOCK_H
#define FLOORBLOCK_H

#include "Block.h"
#include "../Characters/Player.h"
#include "../Maps/Room.h"

class FloorBlock : public Block
{
 public:
	 FloorBlock(int posx, int posy, Player& player, Room& room, SDL_Renderer* renderer);
};

#endif
