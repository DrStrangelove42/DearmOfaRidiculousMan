#ifndef WALLBLOCK_H
#define WALLBLOCK_H

#include "Block.h"
#include "../Maps/Room.h"

class WallBlock : public Block
{
 public:
	 WallBlock(int x, int y, Player& player, Room& room, SDL_Renderer* renderer);
};

#endif
