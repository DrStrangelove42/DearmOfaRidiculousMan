#include "Block.h"

Block::Block(int posx, int posy, Player* player, string tx) : x(posx), y(posy), player(player), texture(tx)
{
	
}

int Block::getX()
{
	return x;
}

int Block::getY()
{
	return y;
}

int Block::render(SDL_Renderer renderer)
{
	DrawImage(renderer, texture, x * SZ_BLOCKSIZE, y * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
}