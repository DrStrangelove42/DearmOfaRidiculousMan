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

void Item::useItem()
{
}

void Item::tick(int time)
{

}
