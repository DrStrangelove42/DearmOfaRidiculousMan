#include "LivingEntity.h"

void LivingEntity::damage(int dmg)
{
	if (health - dmg >= 0)
		health -= dmg;
	else
		kill();
}

bool LivingEntity::isAlive()
{
	return health > 0;
}

void LivingEntity::drawHealthBar(RenderContext& renderer, int x, int y)
{
	renderer.changeColor(0x00FF00FF);
	renderer.drawRectangle(x, y, health * (SZ_BLOCKSIZE * 2) / maxHealth, SZ_BLOCKSIZE / 2, true);
	renderer.changeColor(0xFFFFFFFF);
	renderer.drawRectangle(x - 1, y - 1, SZ_BLOCKSIZE * 2 + 1, SZ_BLOCKSIZE / 2 + 1);
}