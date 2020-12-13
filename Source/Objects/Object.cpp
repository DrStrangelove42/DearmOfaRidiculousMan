#include "Object.h"

Object::Object(string identifier, int posx, int posy, string tx, RenderContext& renderer, bool trav, int attack, int defense) :
	MovingEntity(posx, posy, renderer, tx), id(identifier), traversable(trav), attack(attack), defense(defense)
{

}

Object::Object(const Object& other) : MovingEntity(other), id(other.id), traversable(other.traversable), attack(other.attack), defense(other.defense) {}

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

string Object::getId() const
{
	return id;
}

void Object::updateObject(GAME* g)
{

}

void Object::tick(int time, GAME* g)
{

}
