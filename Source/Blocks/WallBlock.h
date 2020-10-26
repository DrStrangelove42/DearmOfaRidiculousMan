#ifndef WALLBLOCK_H
#define WALLBLOCK_H

#include "Block.h"

class WallBlock : public Block
{
 public:
	 WallBlock(int x, int y, Player* player);
};

#endif
