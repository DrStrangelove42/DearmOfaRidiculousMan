#ifndef FLOORBLOCK_H
#define FLOORBLOCK_H

#include "Block.h"
#include "../Characters/Player.h"

class FloorBlock : public Block
{
public:
	FloorBlock(int posx, int posy, Player& player, RenderContext& renderer);
};

#endif
