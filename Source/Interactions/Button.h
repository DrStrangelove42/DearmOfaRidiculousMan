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

	int id;
public:
	Button(Texture* texture, int x, int y, int id, function<void(int)> onClick);

	Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color=0xffffffff);

	void onMouseEvent(MOUSE_DATA* md);
	virtual void tick(int time, RenderContext&);
};

#endif