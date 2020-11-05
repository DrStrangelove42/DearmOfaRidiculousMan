#include "FloorBlock.h"

FloorBlock::FloorBlock(int posx, int posy, Player &player, Room& room, SDL_Renderer* renderer) : Block(posx, posy, player, room, "floor", renderer)
{

}