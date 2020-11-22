#include "Monster.h"
#include <stdlib.h>
Monster::Monster(RenderContext& renderer,
	Player& p,
	string textureId,
	int health,
	int dmg,
	int atkDelay,
	int atkRadius,
	int coins,
	int exp, bool alarmed) :
        LivingEntity(health, coins, exp), attackValue(dmg), player(p), attackDelay(atkDelay), attackRadius(atkRadius), Alarmed(alarmed)
{
	texture = LoadTexture(textureId, renderer);
}

void Monster::kill()
{
	player.getExperience(experience);
	player.getCoins(money);
}

void Monster::tick(int time, RenderContext& r)
{
	static int lastTime = 0;
	if (time - lastTime >= attackDelay)
	{
		lastTime = time;
		alarm();
		attackRound();
	}
}

void Monster::attackRound()
{
	if (abs(x - player.getX()) < attackRadius && abs(y - player.getY()) < attackRadius)
	{
		player.damage(attackValue);
	}
}

void Monster::alarm()
{
	if (abs(x - player.getX()) < alarmRadius && abs(y - player.getY()) < alarmRadius)
	{
		alarmed = true;
	}
}

void Monster::render(RenderContext& renderer, int offsetX, int offsetY)
{
	int xx = (x + offsetX) * SZ_BLOCKSIZE;
	int yy = (y + offsetY) * SZ_BLOCKSIZE;
	texture->render(renderer, xx, yy, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
	drawHealthBar(renderer, xx, yy);
}
