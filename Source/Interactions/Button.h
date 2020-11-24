#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <functional>
#include "../Base/Texture.h"
#include "../Base/Entity.h"
#include "../Base/utils.h"

using namespace std;

class Button : public Entity
{
protected:
	Texture* texture;

	/// <summary>
	/// The callback takes the button ID as a parameter.
	/// </summary>
	function<void(int)> onClick;

	int x;
	int y;
	int id;
public:
	Button(Texture* texture, int x, int y, int id, function<void(int)> onClick);

	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	void onMouseEvent(MOUSE_DATA* md);
	virtual void tick(int time, RenderContext&);
};

#endif