#include "Object.h"

Object::Object(string identifier, int posx, int posy, Player& p, string tx, RenderContext& renderer, bool trav) : id(identifier), x(posx), y(posy), player(p), texture(tx), traversable(trav)
{
	updateTexture(renderer);
}

Object::Object(const Object& other) : id(other.id), x(other.x), y(other.y), player(other.player), texture(other.texture), loadedTx(other.loadedTx), traversable(other.traversable)
{
  
}

Object::~Object()
{

}

void Object::updateTexture(RenderContext& renderer)
{
	loadedTx = LoadTexture(texture, renderer);
}

int Object::getX()
{
	return x;
}

int Object::getY()
{
	return y;
}

string Object::getId() const
{
	return id;
}

bool Object::getTrav()
{
	return traversable;
}

void Object::move(int px, int py)
{
	x = px; y = py;
}

void Object::render(RenderContext& renderer, int offsetX, int offsetY)
{
	loadedTx->render(renderer, (x + offsetX) * SZ_BLOCKSIZE, (y + offsetY) * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
}

void Object::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea)
{
}

void Object::tick(int time, RenderContext& renderer)
{

}
