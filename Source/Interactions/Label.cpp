#include "Label.h"

Label::Label(Texture* texture, int x, int y) : texture(texture), x(x), y(y)
{

}

Label::Label(string caption, RenderContext& r, int x, int y, int color) : x(x), y(y)
{
	texture = LoadString(caption, r, color);
}

void Label::render(RenderContext& renderer, int offsetX, int offsetY)
{
	texture->renderUnscaled(renderer, x + SZ_BLOCKSIZE * offsetX, y + SZ_BLOCKSIZE * offsetY);
}

void Label::tick(int time, RenderContext& r)
{

}