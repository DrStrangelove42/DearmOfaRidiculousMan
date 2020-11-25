#ifndef MOVING_H
#define MOVING_H

#include "../Base/Entity.h"

/*
Objects in the game that can be moved.
*/
class MovingEntity : public Entity
{
protected:
	/* Coordinates of the entity */
	int x;
	int y;

public:
	MovingEntity();
	MovingEntity(int x, int y);
	/* Moves the entity to (x, y) */
	void teleport(int x, int y);
	/* Accessors */
	int getX();
	int getY();
};

#endif