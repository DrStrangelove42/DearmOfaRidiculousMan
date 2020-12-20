#include "DrawableEntity.h"

DrawableEntity::DrawableEntity(int x, int y, RenderContext& renderer, string tx) :x(x), y(y), texture(tx)
{
	updateTexture(renderer);
}

DrawableEntity::DrawableEntity(int x, int y, Texture* tx) : x(x), y(y), texture(""), loadedTx(tx)
{
}

void DrawableEntity::updateTexture(RenderContext& renderer)
{
	if (!texture.empty())
		loadedTx = LoadTexture(texture, renderer);
}

void DrawableEntity::setTexture(Texture* texture)
{
	loadedTx = texture;
}

void DrawableEntity::render(RenderContext& renderer, int offsetX, int offsetY)
{
	int xx = (x + offsetX);
	int yy = (y + offsetY);
	if (xx < BLOCKS_W && yy < BLOCKS_H)
	{
		loadedTx->render(renderer, xx * SZ_BLOCKSIZE, yy * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
	}
}

string& DrawableEntity::getTextureID()
{
	return texture;
}
