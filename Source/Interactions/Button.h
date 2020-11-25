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
	bool mouseOver;
	int id;
	Texture* overTexture;
	Texture* normalTexture;
public:
	Button(Texture* texture, int x, int y, int id, function<void(int)> onClick);

	Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color = 0xffffffff);

	Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color, int OverColor);

	void onMouseEvent(MOUSE_DATA* md);
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	virtual void tick(int time, RenderContext&);
};

#endif