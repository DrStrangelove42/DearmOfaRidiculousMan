#include "Item.h"

Item::Item(string tx, RenderContext& renderer) : texture(tx)
{
	updateTexture(renderer);
} 

Item::~Item()
{

}

void Item::updateTexture(RenderContext& renderer)
{
	loadedTx = LoadTexture(texture, renderer);
}

void Item::render(RenderContext& renderer, int offsetX, int offsetY)
{
	loadedTx->render(renderer, (x + offsetX) * SZ_BLOCKSIZE, (y + offsetY) * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
}

void Item::teleportOn(MovingEntity& m)
{
	m.teleport(x, y);
}

void Item::useItem()
{
}

void Item::tick(int time)
{

}
