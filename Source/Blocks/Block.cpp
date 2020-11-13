#include "Block.h"

Block::Block(int posx, int posy, string tx, RenderContext& renderer) : x(posx), y(posy), traversable(false), texture(tx)
{
	updateTexture(renderer);
} 

Block::~Block()
{

}

void Block::updateTexture(RenderContext& renderer)
{
	loadedTx = LoadTexture(texture, renderer);
}

void Block::render(RenderContext& renderer, int offsetX, int offsetY)
{
	loadedTx->render(renderer, (x + offsetX) * SZ_BLOCKSIZE, (y + offsetY) * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
}

void Block::teleportOn(MovingEntity& m)
{
	m.teleport(x, y);
}

void Block::tick(int time)
{

}

//void Block::onEnter(EVENT_ARGS* ea)
//{
	/* Just ignores the move, because we are an empty block. (?Todo) */
//}
