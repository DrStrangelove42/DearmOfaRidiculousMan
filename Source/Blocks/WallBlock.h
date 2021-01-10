#ifndef WALLBLOCK_H
#define WALLBLOCK_H

#include "Block.h"

/// <summary>
/// A WallBlock is a type of Block that generally composes the walls of a Room. It isn't <see cref="WallBlock::traversable">traversable</see>, and the Texture can be chosen.
/// </summary>
class WallBlock : public Block
{
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="renderer"></param>
	WallBlock(int posx, int posy, RenderContext& renderer, string texture="wall");
};

#endif
