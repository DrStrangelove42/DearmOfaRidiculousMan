#include "Block.h"

Block::Block(int posx, int posy, string tx, RenderContext& renderer, bool trav) : DrawableEntity(posx, posy, renderer, tx), traversable(trav)
{}

Block::~Block()
{

}

int Block::getX()
{
	return x;
}

int Block::getY()
{
	return y;
}

bool Block::getTrav()
{
	return traversable;
}

void Block::setTrav(bool t)
{
	traversable = t;
}

void Block::teleportOn(MovingEntity& m)
{
	m.teleport(x, y);
}

void Block::tick(int time, GAME* game)
{

}
