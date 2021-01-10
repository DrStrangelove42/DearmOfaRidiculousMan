#ifndef FLOORBLOCK_H
#define FLOORBLOCK_H

#include "Block.h"
#include "../Characters/Player.h"

/// <summary>
/// A FloorBlock is a type of Block that generally composes the floor of a Room. It is <see cref="FloorBlock::traversable">traversable</see>, and the Texture can be chosen.
/// </summary>
class FloorBlock : public Block
{
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="renderer"></param>
	FloorBlock(int posx, int posy, RenderContext& renderer, string texture = "floor");
};

#endif
