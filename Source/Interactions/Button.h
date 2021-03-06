#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>
#include "../Base/Texture.h"
#include "Label.h"
#include "../Base/utils.h"
#include "../Base/game.h"

using namespace std;

/// <summary>
/// A Button is a Label that can be clicked on by the user to perform a certain action.
/// </summary>
class Button : public Label
{
protected:
	string name;
	/// <summary>
	/// The callback takes the button ID as a parameter.
	/// </summary>
	function<void(int)> onClick;
	/// <summary>
	/// If the mouse is currently hovering over the button.
	/// </summary>
	bool mouseOver;
	/// <summary>
	/// The button id, sent to the callback function.
	/// </summary>
	int id;
	/// <summary>
	/// Field keeping the texture drawn when the mouse hovers the button.
	/// </summary>
	Texture* overTexture;
	/// <summary>
	/// Field keeping the texture drawn in inactive mode.
	/// </summary>
	Texture* normalTexture;

	/// <summary>
	/// Selection rectangle color
	/// </summary>
	int overClr;

	/// <summary>
	/// The margin used to draw a rectangle surrounding the contents of the button (all sides).
	/// </summary>
	int outerMargin;
public:
	/// <summary>
	/// Creates a new button.
	/// </summary>
	/// <param name="texture">A pointer to an already created texture</param>
	/// <param name="x">X coordinate (screen coordinates)</param>
	/// <param name="y">Y coordinate (screen coordinates)</param>
	/// <param name="id">Identifier that is the parameter of the callback function.</param>
	/// <param name="onClick">Callback function called when the user clicks on the button.</param>
	Button(Texture* texture, int x, int y, int id, function<void(int)> onClick);
	/// <summary>
	/// Creates a new button.
	/// </summary>
	/// <param name="caption">Text of the button</param>
	/// <param name="r">The render context used to create the underlying texture.</param>
	/// <param name="x">X coordinate (screen coordinates)</param>
	/// <param name="y">Y coordinate (screen coordinates)</param>
	/// <param name="id">Identifier that is the parameter of the callback function.</param>
	/// <param name="onClick">Callback function called when the user clicks on the button.</param>
	/// <param name="color">Text color, white by default</param>
	Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color = 0xffffffff);
	/// <summary>
	/// Creates a new button.
	/// </summary>
	/// <param name="caption">Text of the button</param>
	/// <param name="r">The render context used to create the underlying texture.</param>
	/// <param name="x">X coordinate (screen coordinates)</param>
	/// <param name="y">Y coordinate (screen coordinates)</param>
	/// <param name="id">Identifier that is the parameter of the callback function.</param>
	/// <param name="onClick">Callback function called when the user clicks on the button.</param>
	/// <param name="color">Text color.</param>
	/// <param name="OverColor">Text color in active mode.</param>
	Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color, int OverColor);
	/// <summary>
	/// Catches the mouse status of the container.
	/// </summary>
	/// <param name="md">Mouse data.</param>
	void onMouseEvent(MOUSE_DATA* md);
	/// <summary>
	/// For buttons, the rendering is in absolute position (no offset).
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX">Ignored.</param>
	/// <param name="offsetY">Ignored.</param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)const;
	/// <summary>
	/// Time management
	/// </summary>
	/// <param name="time">Current instant in the game</param>
	/// <param name="game">The game structure.</param>
	virtual void tick(int time, GAME* game);
};

#endif
