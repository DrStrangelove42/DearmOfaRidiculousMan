#include "MovingEntity.h"

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