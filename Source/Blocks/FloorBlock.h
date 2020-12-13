#ifndef FLOORBLOCK_H
#define FLOORBLOCK_H

#include "Block.h"
#include "../Characters/Player.h"

class FloorBlock : public Block
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	FloorBlock(int posx, int posy, RenderContext& renderer);
	FloorBlock(int posx, int posy, RenderContext& renderer, string texture);
};

#endif
