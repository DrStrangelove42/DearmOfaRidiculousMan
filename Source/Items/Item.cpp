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

void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)
{
	//Do not render anything as an Item is abstract for us.
}

void Item::tick(int time)
{

}

string Item::getId() const
{
	//TODO
}
