#include "Button.h"

Button::Button(Texture* texture, int x, int y, int id, function<void(int)> onClick) : Label(texture, x, y), id(id), onClick(onClick)
{

}

Button::Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color) : Label(caption, r, x, y, color), id(id), onClick(onClick)
{

}

void Button::onMouseEvent(MOUSE_DATA* md)
{
	if (x + texture->getWidth() >= md->x && md->x >= x &&
		y + texture->getHeight() >= md->y && md->y >= y)
	{
		if (md->state == MouseStatePushed && md->button == MouseLeft)
		{
			onClick(id);
		}
	}
}

void Button::tick(int time, RenderContext& r)
{

}