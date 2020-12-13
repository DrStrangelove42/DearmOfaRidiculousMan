#include "FloorBlock.h"

FloorBlock::FloorBlock(int posx, int posy, RenderContext& renderer) : Block(posx, posy, "floor", renderer, true)
{

}

FloorBlock::FloorBlock(int posx, int posy, RenderContext& renderer, string texture) : Block(posx, posy, texture, renderer, true)
{

}