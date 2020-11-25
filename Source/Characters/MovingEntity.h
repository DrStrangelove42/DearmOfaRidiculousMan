#ifndef MOVING_H
#define MOVING_H

#include "../Base/Entity.h"

/// <summary>
/// Objects in the game that can be moved.
/// </summary>
class MovingEntity : public Entity
{
protected:
	/* Coordinates of the entity */
	int x;
	int y;

public:
	MovingEntity();
	MovingEntity(int x, int y);
	/// <summary>
	/// Moves the entity to (x, y)
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void teleport(int x, int y);
	/* Accessors */
	int getX();
	int getY();
};

#endif