#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <functional>
#include "../Base/Texture.h"
#include "../Characters/MovingEntity.h"
#include "../Base/utils.h"
#include "../Base/game.h"

using namespace std;

/// <summary>
/// A Label is an Entity that displays text.
/// </summary>
class Label : public MovingEntity
{
public:
	/// <summary>
	/// Creates a new label.
	/// </summary>
	/// <param name="texture">A pointer to an already created texture</param>
	/// <param name="x">X coordinate (screen coordinates)</param>
	/// <param name="y">Y coordinate (screen coordinates)</param>
	Label(Texture* texture, int x, int y);
	/// <summary>
	/// Creates a new label.
	/// </summary>
	/// <param name="caption">Text of the label</param>
	/// <param name="r">The render context used to create the underlying texture.</param>
	/// <param name="x">X coordinate (screen coordinates)</param>
	/// <param name="y">Y coordinate (screen coordinates)</param>
	/// <param name="color">Text color, white by default</param>
	Label(string caption, RenderContext& r, int x, int y, int color = 0xffffffff);

	/// <summary>
	/// Render the label.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX">X offset.</param>
	/// <param name="offsetY">Y offset.</param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0) const;
	/// <summary>
	/// Time management
	/// </summary>
	/// <param name="time">Current instant in the game</param>
	/// <param name="game">The game structure.</param>
	virtual void tick(int time, GAME* game);
};

#endif
