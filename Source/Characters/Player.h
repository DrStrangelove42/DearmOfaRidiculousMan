#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"

class Player : public Entity
{
protected:
	int health;
	int maxHealth;
	int lives;
	int x;
	int y;
	SDL_Texture* texture;
public:
	Player();
	Player(SDL_Renderer* renderer);
	void damage(int dmg);
	bool isAlive();
	void kill();
	void render(SDL_Renderer* renderer);
};

#endif