#include "Object.h"

Object::Object(string identifier, int posx, int posy, string tx, RenderContext& renderer, bool trav, string info) :
	MovingEntity(posx, posy, renderer, tx), id(identifier), traversable(trav), info(info)
{

}

Object::Object(const Object& other) : MovingEntity(other), id(other.id), traversable(other.traversable) {}

bool Object::getTrav() const
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

string Object::getId() const
{
	return id;
}

bool Object::updateObject(GAME* g)
{
	return false;
}

void Object::tick(int time, GAME* g)
{

}

string Object::objectToString() const
{
	return "Basic object";
}

string Object::getInfo() const
{
	return info;
}
