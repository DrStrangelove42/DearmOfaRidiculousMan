#include "Button.h"

Button::Button(Texture* texture, int x, int y, int id, function<void(int)> onClick) : Label(texture, x, y), id(id), onClick(onClick), mouseOver(false), overTexture(NULL)
{
	normalTexture = texture;
}

Button::Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color) : Label(caption, r, x, y, color), id(id), onClick(onClick), mouseOver(false), overTexture(NULL)
{
	normalTexture = loadedTx;
}

Button::Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color, int overColor) :
	Label(caption, r, x, y, color), id(id), onClick(onClick), mouseOver(false)
{
	overTexture = LoadString(caption, r, overColor);
	normalTexture = loadedTx;
}

void Button::onMouseEvent(MOUSE_DATA* md)
{
	if (x + loadedTx->getWidth() + SZ_BLOCKSIZE >= md->x && md->x >= x - SZ_BLOCKSIZE &&
		y + loadedTx->getHeight() + SZ_BLOCKSIZE >= md->y && md->y >= y - SZ_BLOCKSIZE)
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
			loadedTx = overTexture;
			renderer.changeColor(0xffffffff);
			renderer.drawRectangle(x - SZ_BLOCKSIZE, y - SZ_BLOCKSIZE, loadedTx->getWidth() + 2 * SZ_BLOCKSIZE, loadedTx->getHeight() + 2 * SZ_BLOCKSIZE);
		}
		else
		{
			loadedTx = normalTexture;
		}
	} 
	Label::render(renderer, offsetX, offsetY);
}

void Button::tick(int time, RenderContext& r, GAME* game)
{

}
