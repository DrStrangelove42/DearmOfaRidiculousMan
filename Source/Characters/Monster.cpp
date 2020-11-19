#include "Monster.h"

Monster::Monster(RenderContext& renderer,
	Player& p,
	string textureId,
	int dmg,
	int atkDelay,
	int atkRadius,
	int coins,
	int exp) :
	damage(dmg), player(p), attackDelay(atkDelay), attackRadius(atkRadius)
{
	money = coins;
	experience = exp;
	texture = LoadTexture(textureId, renderer);
}

void Monster::kill()
{
	player.getExperience(experience);
	player.getCoins(money);
}

void Monster::tick(int time)
{
	static int lastTime = 0;
	if (time - lastTime >= attackDelay)
	{
		lastTime = time;
		attackRound();
	}
}

void Monster::attackRound()
{
	if (abs(x - player.getX()) < attackRadius && abs(y - player.getY()) < attackRadius)
	{
		player.damage(damage);
	}
}

void Monster::render(RenderContext& renderer, int offsetX, int offsetY)
{
	int xx = (x + offsetX) * SZ_BLOCKSIZE;
	int yy = (y + offsetY) * SZ_BLOCKSIZE;
	texture->render(renderer, xx, yy, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
	drawHealthBar(renderer, xx, yy);
}