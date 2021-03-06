#include "Button.h"

Button::Button(Texture* texture, int x, int y, int id, function<void(int)> onClick) :
	Label(texture, x, y), id(id), onClick(onClick), mouseOver(false), overTexture(NULL), name("noname"), overClr(0xFFFFFFFF), outerMargin(SZ_BLOCKSIZE - 2)
{

	normalTexture = texture;
}

Button::Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color) :
	Label(caption, r, x, y, color), id(id), onClick(onClick), mouseOver(false), overTexture(NULL), name(caption), overClr(0xFFFFFFFF), outerMargin(SZ_BLOCKSIZE - 2)
{
	normalTexture = loadedTx;
}

Button::Button(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color, int overColor) :
	Label(caption, r, x, y, color), id(id), onClick(onClick), mouseOver(false), name(caption), overClr(overColor), outerMargin(SZ_BLOCKSIZE - 2)
{
	overTexture = r.LoadString(caption, overColor);
	normalTexture = loadedTx;
}

void Button::onMouseEvent(MOUSE_DATA* md)
{
	if (x + loadedTx->getWidth() + outerMargin >= md->x && md->x >= x - outerMargin &&
		y + loadedTx->getHeight() + outerMargin >= md->y && md->y >= y - outerMargin)
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

void Button::render(RenderContext& renderer, int offsetX, int offsetY) const
{
	if (mouseOver)
	{
		renderer.changeColor(overClr);
		renderer.drawRectangle(x - outerMargin, y - outerMargin, loadedTx->getWidth() + 2 * outerMargin, loadedTx->getHeight() + 2 * outerMargin);
	}

	Label::render(renderer, offsetX, offsetY);
}

void Button::tick(int time, GAME* game)
{
	if (overTexture != NULL)
	{
		if (mouseOver)
		{
			loadedTx = overTexture;
		}
		else
		{
			loadedTx = normalTexture;
		}
	}
}
