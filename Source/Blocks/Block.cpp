#include "Block.h"

Block::Block() {}

Block::Block(int posx, int posy, Player p, string tx, SDL_Renderer* renderer) : x(posx), y(posy), player(p), texture(tx)
{
	loadedTx = LoadTexture(tx, renderer);
}

Block::Block(Player p) : player(p)
{

}

Block::~Block()
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

void Block::move(int px, int py)
{
	x = px; y = py;
}

void Block::render(SDL_Renderer* renderer)
{
  //printf("render block(%d,%d)\n", x, y);
	DrawImage(renderer, loadedTx, x * SZ_BLOCKSIZE, y * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
}

void Block::tick(int time)
{

}