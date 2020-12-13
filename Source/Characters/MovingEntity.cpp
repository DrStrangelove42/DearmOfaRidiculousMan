#include "MovingEntity.h"

MovingEntity::MovingEntity(int x, int y, RenderContext& renderer, string texture) : DrawableEntity(x, y, renderer, texture)
{

}

MovingEntity::MovingEntity(int x, int y, Texture* text) : DrawableEntity(x, y, text)
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