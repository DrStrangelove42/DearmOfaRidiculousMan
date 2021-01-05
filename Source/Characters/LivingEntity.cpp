#include "LivingEntity.h"
#include <iostream>

LivingEntity::LivingEntity(int startHealth, int startMoney, int startExp) : health(startHealth), maxHealth(startHealth), money(startMoney), experience(startExp)
{

}

void LivingEntity::damage(int dmg)
{
	if (isAlive())
	{
		health -= dmg;
		if (health <= 0)
			kill();
	}
}

bool LivingEntity::isAlive()const
{
	return health > 0;
}

void LivingEntity::drawHealthBar(RenderContext& renderer, int x, int y) const
{
	static int sz4 = SZ_BLOCKSIZE >> 2;
	static int sz2 = SZ_BLOCKSIZE >> 1;
	int X = x - sz4;
	int Y = y - sz2;
	renderer.changeColor(0xFFFFFFFF);
	renderer.drawRectangle(X, Y, int(SZ_BLOCKSIZE * 1.5) - 1, sz4 - 1, true);
	renderer.changeColor(0x00FF00FF);
	renderer.drawRectangle(X, Y, int(health * SZ_BLOCKSIZE * 1.5 / maxHealth) - 1, sz4, true);
	renderer.changeColor(0x00000000);
	renderer.drawRectangle(X - 1, Y - 1, int(SZ_BLOCKSIZE * 1.5) + 1, sz4 + 1);
}

int LivingEntity::getHealth()
{
	return health;
}

int LivingEntity::getMaxHealth()
{
	return maxHealth;
}

int LivingEntity::getMoney()
{
	return money;
}

int LivingEntity::getExperience()
{
	return experience;
}

void LivingEntity::setHealth(int h)
{
	health = h;
}
  
void LivingEntity::setMaxHealth(int mh)
{
	maxHealth = mh;
}

void LivingEntity::setMoney(int mon)
{
	money = mon;
}

void LivingEntity::setExperience(int exp)
{
	experience = exp;
}
