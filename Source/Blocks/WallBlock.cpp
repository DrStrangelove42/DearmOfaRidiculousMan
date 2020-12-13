#include "WallBlock.h"

WallBlock::WallBlock(int posx, int posy, RenderContext& renderer) : Block(posx, posy, "wall", renderer)
{

}

WallBlock::WallBlock(int posx, int posy, RenderContext& renderer, string texture) : Block(posx, posy, texture, renderer)
{

}
