#include "FloorBlock.h"

FloorBlock::FloorBlock(int posx, int posy, Player &player, RenderContext& renderer) : Block(posx, posy, player, "floor", renderer)
{

}

void FloorBlock::onEnter(EVENT_ARGS* ea)
{
	teleportOn(player);
}