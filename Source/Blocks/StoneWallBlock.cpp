#include "StoneWallBlock.h"

StoneWallBlock::StoneWallBlock(int posx, int posy, RenderContext& renderer) : WallBlock(posx, posy, renderer)
{
	texture = "stonewall";
	updateTexture(renderer);
}
