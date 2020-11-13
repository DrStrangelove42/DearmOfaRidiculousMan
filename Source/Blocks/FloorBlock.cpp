#include "FloorBlock.h"

FloorBlock::FloorBlock(int posx, int posy, RenderContext& renderer) : Block(posx, posy, "floor", renderer), traversable(*(true))
{

}

//void FloorBlock::onEnter(EVENT_ARGS* ea)
//{
//	teleportOn(player);
//}
