#ifndef MOVING_H
#define MOVING_H

#include "../Base/Entity.h"

/*
Objects in the game that can be moved.
*/
class MovingEntity : public Entity
{
protected:
	int x;
	int y;

public:
	//virtual MovingEntity() = 0;
	void teleport(int x, int y);
	int getX();
	int getY();
};

#endif