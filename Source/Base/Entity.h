#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

class Entity
{
public:
	Entity();
	void render(SDL_Renderer* renderer);
	void tick(int time);
};

#endif