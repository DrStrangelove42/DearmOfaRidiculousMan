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

}
