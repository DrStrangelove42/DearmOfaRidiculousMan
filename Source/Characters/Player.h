#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"

class Player : public Entity
{
protected:
	int health;
	int lives;
	int x;
	int y;
	SDL_Texture texture;
public:
	 Player();
	 void damage(int dmg);
	 bool isAlive();
};

#endif