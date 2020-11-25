#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>
#include "../Base/Texture.h"
#include "Label.h"
#include "../Base/utils.h"

using namespace std;

class Button : public Label
{
protected:
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
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	virtual void tick(int time, RenderContext&);
};

#endif