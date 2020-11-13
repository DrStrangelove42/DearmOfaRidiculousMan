#ifndef LIVING_H
#define LIVING_H

#include "../Base/Entity.h"

/*
Objects in the game that can be moved.
*/
class LivingEntity : public Entity
{
protected:
	/* Health points of the player : when this reaches 0,
	   the player lose a life (see <lives> field below) */
	int health;
	/* HP count (health points) */
	int maxHealth;
	/* Number of lives until game over. */
	int lives;

public:
	void damage(int dmg);
	bool isAlive();
	void kill();

};

#endif