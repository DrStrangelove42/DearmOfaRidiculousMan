#include "Button.h"

Button::Button(Texture* texture, int x, int y, int id, function<void(int)> onClick) : Label(texture, x, y), id(id), onClick(onClick),mouseOver(false),overTexture(NULL)
{
	normalTexture = texture;
}

Button::Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color) : Label(caption, r, x, y, color), id(id), onClick(onClick), mouseOver(false), overTexture(NULL)
{
	normalTexture = texture;
}

Button::Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color, int overColor) : 
	Label(caption, r, x, y, color), id(id), onClick(onClick), mouseOver(false)
{
	overTexture = LoadString(caption, r, overColor);
	normalTexture = texture;
}

void Button::onMouseEvent(MOUSE_DATA* md)
{
	if (x + texture->getWidth() >= md->x && md->x >= x &&
		y + texture->getHeight() >= md->y && md->y >= y)
	{
		mouseOver = true;
		if (md->state == MouseStatePushed && md->button == MouseLeft)
		{
			onClick(id);
		}
	}
	else
		mouseOver = false;
}

void Button::render(RenderContext& renderer, int offsetX, int offsetY)
{
	if (overTexture != NULL)
	{
		if (mouseOver)
		{
			texture = overTexture;
		}
		else
		{
			texture = normalTexture;
		}
	}
	Label::render(renderer, offsetX, offsetY);
}

void Button::tick(int time, RenderContext& r, GAME* game)
{

}
