#include "WallBlock.h"

WallBlock::WallBlock(int posx, int posy, Player& player, Room& room, SDL_Renderer* renderer) : Block(posx, posy, player, room, "wall", renderer)
{

}