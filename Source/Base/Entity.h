#ifndef ENTITY_H
#define ENTITY_H

#include "RenderContext.h"
#include "game.h"
#include <iostream>
using namespace std;

/// <summary>
/// An Entity is something that is visible and can be rendered in the Window.
/// </summary>
class Entity
{
public:
	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~Entity() { };
	
	/// <summary>
	/// <see cref="RenderContext">Rendering</see> method, enabling the <see cref="RenderContext::renderer">renderer</see> to take the offset (in <see cref="Block">blocks</see>) into account.
	/// </summary>
	/// <param name="renderer">The rendering context on which to render elements.</param>
	/// <param name="offsetX">X Offset, in blocks</param>
	/// <param name="offsetY">Y Offset, in blocks</param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0) const = 0;

	/// <summary>
	/// Time management.
	/// </summary>
	/// <param name="time"></param>
	/// <param name=""></param>
	virtual void tick(int time, GAME* game) = 0;
};

#endif
