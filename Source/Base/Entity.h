#ifndef ENTITY_H
#define ENTITY_H

#include "RenderContext.h"
/*
Every visible object in the window is an Entity.
*/
class Entity
{
protected:
 
public:
	/// <summary>
	/// Standard destructor.
	/// </summary>
	virtual ~Entity() {};
	
	/// <summary>
	/// Rendering method, enabling the renderer to take the offset (in blocks) into account.
	/// </summary>
	/// <param name="renderer">The rendering context on which to render elements.</param>
	/// <param name="offsetX">X Offset, in blocks</param>
	/// <param name="offsetY">Y Offset, in blocks</param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0) = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="time"></param>
	/// <param name=""></param>
	virtual void tick(int time, RenderContext&) = 0;

};

#endif