#include "Shop.h"

Shop::Shop(string identifier, int posx, int posy, string tx, RenderContext& renderer) :
	Object(identifier, posx, posy, tx, renderer, false)
{

}

Shop::~Shop()
{

}

bool Shop::updateObject(GAME* g)
{
	return false;
}

void Shop::tick(int time, GAME* g)
{

}

string Shop::objectToString() const
{
	return "Shop ";//TODO
}

void Shop::render(RenderContext& renderer, int offsetX, int offsetY) const
{
	DrawableEntity::render(renderer, offsetX, offsetY);
}
