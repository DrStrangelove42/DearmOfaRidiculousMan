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
	/// 
	/// </summary>
	bool mouseOver;
	/// <summary>
	/// 
	/// </summary>
	int id;
	/// <summary>
	/// 
	/// </summary>
	Texture* overTexture;
	/// <summary>
	/// 
	/// </summary>
	Texture* normalTexture;

	/// <summary>
	/// Selection rectangle color
	/// </summary>
	int overClr;
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="id"></param>
	/// <param name="onClick"></param>
	Button(Texture* texture, int x, int y, int id, function<void(int)> onClick);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="caption"></param>
	/// <param name="r"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="id"></param>
	/// <param name="onClick"></param>
	/// <param name="color"></param>
	Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color = 0xffffffff);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="caption"></param>
	/// <param name="r"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="id"></param>
	/// <param name="onClick"></param>
	/// <param name="color"></param>
	/// <param name="OverColor"></param>
	Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color, int OverColor);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="md"></param>
	void onMouseEvent(MOUSE_DATA* md);
	/// <summary>
	/// For buttons, the rendering is in absolute position (no offset).
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX">Ignored.</param>
	/// <param name="offsetY">Ignored.</param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)const;
	virtual void tick(int time, GAME* game);
};

#endif
