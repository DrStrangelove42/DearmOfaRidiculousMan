#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"
#include "MovingEntity.h"

class Player : public MovingEntity
{
protected:
	int health;
	int maxHealth;
	int lives;
	SDL_Texture* texture;
public:
	Player(SDL_Renderer* renderer);
	void damage(int dmg);
	bool isAlive();
	void kill();
	void render(SDL_Renderer* renderer);
	
	virtual void tick(int time);
};

#endif