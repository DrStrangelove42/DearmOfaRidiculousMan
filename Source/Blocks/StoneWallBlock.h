#ifndef STONEWALLBLOCK_H
#define STONEWALLBLOCK_H

#include "WallBlock.h"

class StoneWallBlock : public WallBlock
{
 public:
	 /// <summary>
	 /// 
	 /// </summary>
	 /// <param name="x"></param>
	 /// <param name="y"></param>
	 /// <param name="renderer"></param>
	 StoneWallBlock(int x, int y, RenderContext& renderer);
};

#endif
