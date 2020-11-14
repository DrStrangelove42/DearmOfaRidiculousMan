#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"
#include "MovingEntity.h"
#include "LivingEntity.h"

/*
The Player object is the representation of the person
playing the game.
*/
class Player : public MovingEntity, public LivingEntity
{
protected:
	
	/* Number of lives until game over. */
	int lives;
	/* TODO : player's items */

	/* The texture used for the player. */
	Texture* texture;
public:
	/* Creates the player */
	Player(RenderContext& renderer);
	
	virtual void kill();

	/* Rendering management */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	
	/* Time management */
	virtual void tick(int time);

	/* Health points of the player : when this reaches 0,
	   the player lose a life (see <lives> field below) */
	int health;
	/* HP count (health points) */
	int maxHealth;
};

#endif
