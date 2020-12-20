#include "Label.h"

Label::Label(Texture* texture, int x, int y) : MovingEntity(x, y, texture)
{

}

Label::Label(string caption, RenderContext& r, int x, int y, int color) : MovingEntity(x, y, r, "")
{
	loadedTx = LoadString(caption, r, color);
}

void Label::render(RenderContext& renderer, int offsetX, int offsetY) const
{
	loadedTx->renderUnscaled(renderer, x + SZ_BLOCKSIZE * offsetX, y + SZ_BLOCKSIZE * offsetY);
}

void Label::tick(int time, GAME* game)
{

}
