#ifndef MONSTER_H
#define MONSTER_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"
#include "MovingEntity.h"

class Monster : public MovingEntity
{
protected:
	int health;
	int maxHealth;
	SDL_Texture* texture;
public:
	Player(SDL_Renderer* renderer);
	void damage(int dmg);
	bool isAlive();
	void render(SDL_Renderer* renderer);

	virtual void tick(int time);
};

#endif
