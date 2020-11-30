#include "Object.h"

Object::Object(string identifier, int posx, int posy, string tx, RenderContext& renderer, bool trav) : MovingEntity(posx, posy), id(identifier), texture(tx), traversable(trav)
{
	updateTexture(renderer);
}

Object::Object(const Object& other) : MovingEntity(other.x, other.y), id(other.id), texture(other.texture), loadedTx(other.loadedTx), traversable(other.traversable) {}

bool Object::getTrav()
{
	return traversable;
}

void Object::move(int px, int py)
{
	teleport(px, py);
}

Object::~Object()
{

}

void Object::updateTexture(RenderContext& renderer)
{
	loadedTx = LoadTexture(texture, renderer);
}


string Object::getId() const
{
	return id;
}


void Object::render(RenderContext& renderer, int offsetX, int offsetY)
{
	loadedTx->render(renderer, (x + offsetX) * SZ_BLOCKSIZE, (y + offsetY) * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
}

void Object::updateObject(GAME* g)
{
}

void Object::tick(int time, GAME* g)
{

}
