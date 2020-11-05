#include "Block.h"

Block::Block(int posx, int posy, Player& p, Room& room, string tx, SDL_Renderer* renderer) : x(posx), y(posy), player(p), texture(tx), container(room)
{
	loadedTx = LoadTexture(tx, renderer);
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

void Block::teleportOn(MovingEntity& m)
{
	m.teleport(x, y);
}

void Block::tick(int time)
{

}
