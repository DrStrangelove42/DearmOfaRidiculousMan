#include "StoneWallBlock.h"

StoneWallBlock::StoneWallBlock(int posx, int posy, Player& player, RenderContext& renderer) : WallBlock(posx, posy, player, renderer)
{
	texture = "stonewall";
	updateTexture(renderer);
}