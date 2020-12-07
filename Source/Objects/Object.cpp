#include "Object.h"

Object::Object(string identifier, int posx, int posy, string tx, RenderContext& renderer, bool trav, int attack, int defense) : MovingEntity(posx, posy), id(identifier), texture(tx), traversable(trav), attack(attack), defense(defense)
{
	updateTexture(renderer);
}

Object::Object(const Object& other) : MovingEntity(other.x, other.y), id(other.id), texture(other.texture), loadedTx(other.loadedTx), traversable(other.traversable), attack(other.attack), defense(other.defense) {}

bool Object::getTrav()
{
	return traversable;
}

int Object::getAttack()
{
	return attack;
}

int Object::getDefense()
{
	return defense;
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
