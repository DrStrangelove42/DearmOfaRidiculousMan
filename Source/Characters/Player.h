#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"
#include "MovingEntity.h"


/*
The Player object is the representation of the person
playing the game.
*/
class Player : public MovingEntity
{
protected:
	/* Health points of the player : when this reaches 0,
	   the player lose a life (see <lives> field below) */
	int health;
	/* HP count (health points) */
	int maxHealth;
	/* Number of lives until game over. */
	int lives;

	/* The texture used for the player. */
	Texture* texture;
public:
	/* Creates the player */
	Player(RenderContext& renderer);
	/* Applies damage to the player, making him lose HP according to its resistance. */
	void damage(int dmg);
	/* True if the player is alive (more than 0 HP) */
	bool isAlive();
	/* Instantly kills the player. */
	void kill();
	/* Rendering management */
	virtual void render(RenderContext& renderer);
	
	/* Time management */
	virtual void tick(int time);
};

#endif