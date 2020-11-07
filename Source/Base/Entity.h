#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>
#include "RenderContext.h"
/*
Every visible object in the window is an Entity.
*/
class Entity
{
public:
	virtual ~Entity() {}
	virtual void render(RenderContext& renderer) = 0;
	virtual void tick(int time) = 0;

};

#endif