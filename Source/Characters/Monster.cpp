#include "Monster.h"

Monster::Monster(RenderContext& renderer, string textureId, int dmg) : damage(dmg)
{
	texture = LoadTexture(textureId, renderer);
}

void Monster::kill()
{
	//player wins XP? Coins?
}

void Monster::tick(int time)
{
	//Way to get to the player TODO
}

void Monster::render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)
{
	texture->render(renderer, (x + offsetX) * SZ_BLOCKSIZE, (y + offsetY) * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
}