#ifndef WALLBLOCK_H
#define WALLBLOCK_H

#include "Block.h"

class WallBlock : public Block
{
 public:
	 /// <summary>
	 /// 
	 /// </summary>
	 /// <param name="x"></param>
	 /// <param name="y"></param>
	 /// <param name="renderer"></param>
	 WallBlock(int x, int y, RenderContext& renderer);
};

#endif
