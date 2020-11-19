#include "LivingEntity.h"
#include <iostream>

LivingEntity::LivingEntity(int startHealth, int startMoney, int startExp) : health(startHealth), maxHealth(startHealth), money(startMoney), experience(startExp)
{

}

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
	renderer.drawRectangle(x - (SZ_BLOCKSIZE / 4), y - (SZ_BLOCKSIZE / 2), health * (SZ_BLOCKSIZE * 1.5) / maxHealth, SZ_BLOCKSIZE / 4, true);
	renderer.changeColor(0x00000000);
	renderer.drawRectangle(x - (SZ_BLOCKSIZE / 4) - 1, y - (SZ_BLOCKSIZE / 2) - 1, SZ_BLOCKSIZE * 1.5 + 1, SZ_BLOCKSIZE / 4 + 1);
}
