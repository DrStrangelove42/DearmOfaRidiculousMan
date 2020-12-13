#ifndef MOVING_H
#define MOVING_H

#include "../Base/DrawableEntity.h"

/// <summary>
/// Objects in the game that can be moved.
/// </summary>
class MovingEntity : public DrawableEntity
{
protected:

public:
	MovingEntity(int x, int y, RenderContext& renderer, string texture);
	MovingEntity(int x, int y, Texture* text);
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