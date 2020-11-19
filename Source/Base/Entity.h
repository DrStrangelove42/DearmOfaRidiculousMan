#ifndef ENTITY_H
#define ENTITY_H

#include "RenderContext.h"
/*
Every visible object in the window is an Entity.
*/
class Entity
{
public:
	virtual ~Entity() {};
	/* Rendering method, enabling the renderer to take the offset (in blocks) into account. */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0) = 0;
	virtual void tick(int time, RenderContext&) = 0;

};

#endif