#include "Label.h"

Label::Label(Texture* texture, int x, int y) :MovingEntity(x,y), texture(texture) 
{

}

Label::Label(string caption, RenderContext& r, int x, int y, int color) : MovingEntity(x, y)
{
	texture = LoadString(caption, r, color);
}

void Label::setTexture(Texture* t)
{
	texture = t;
}

void Label::render(RenderContext& renderer, int offsetX, int offsetY)
{
	texture->renderUnscaled(renderer, x + SZ_BLOCKSIZE * offsetX, y + SZ_BLOCKSIZE * offsetY);
}

void Label::tick(int time, RenderContext& r, GAME* game)
{

}
