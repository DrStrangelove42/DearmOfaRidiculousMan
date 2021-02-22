#include "LivingEntity.h"
#include <iostream>

LivingEntity::LivingEntity(int startHealth, int startMoney, int startExp, int defense) :
	defense(defense), health(startHealth), maxHealth(startHealth), money(startMoney), experience(startExp)
{

}

void LivingEntity::damage(int dmg)
{
	if (isAlive())
	{
		health -= max(0, dmg - defense);
		if (health <= 0)
			kill();
	}
}

int LivingEntity::getDefense()
{
	return defense;
}

void  LivingEntity::addDefense(int toAdd)
{
	if (defense + toAdd >= 0)
		defense += toAdd;
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
	renderer.drawRectangle(X, Y, int(min(health * SZ_BLOCKSIZE, 0xffffff) * 1.5 / maxHealth) - 1, sz4, true);
	renderer.changeColor(0x000000FF);
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

void LivingEntity::addMoney(int mon)
{
	money += mon;
}

void LivingEntity::setExperience(int exp)
{
	experience = exp;
}
