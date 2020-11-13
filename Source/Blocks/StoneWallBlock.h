#ifndef STONEWALLBLOCK_H
#define STONEWALLBLOCK_H

#include "WallBlock.h"

class StoneWallBlock : public WallBlock
{
 public:
	 StoneWallBlock(int x, int y, RenderContext& renderer);
};

#endif
