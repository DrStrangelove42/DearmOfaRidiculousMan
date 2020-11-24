#include "Button.h"

Button::Button(Texture* texture, int x, int y, int id, function<void(int)> onClick) : texture(texture), x(x), y(y), id(id), onClick(onClick)
{

}

void Button::render(RenderContext& renderer, int offsetX, int offsetY)
{
	texture->renderUnscaled(renderer, x + SZ_BLOCKSIZE * offsetX, y + SZ_BLOCKSIZE * offsetY);
}

void Button::onMouseEvent(MOUSE_DATA* md)
{

}

void Button::tick(int time, RenderContext& r)
{

}