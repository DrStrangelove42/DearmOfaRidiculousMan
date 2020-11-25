#include "MovingEntity.h"

MovingEntity::MovingEntity() :x(0), y(0)
{

}

MovingEntity::MovingEntity(int x, int y) : x(x), y(y)
{

}

void MovingEntity::teleport(int nx, int ny)
{
	x = nx;
	y = ny;
}

int MovingEntity::getX()
{
	return x;
}

int MovingEntity::getY()
{
	return y;
}