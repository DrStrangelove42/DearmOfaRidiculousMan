#ifndef LIVING_H
#define LIVING_H

#include "../Base/Entity.h"

/*
Objects in the game that can be moved.
*/
class LivingEntity : public Entity
{
protected:
	/* Health points of the entity */
	int health;
	/* HP count (health points) */
	int maxHealth;

public:
	/* Applies damage to the player, making him lose HP according to its resistance. */
	void damage(int dmg);
	/* True if the player is alive (more than 0 HP) */
	bool isAlive();
	/* Instantly kills the entity (pure virtual). */
	virtual void kill() = 0;

};

#endif