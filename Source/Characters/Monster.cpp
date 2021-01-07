#include "Monster.h"
#include "../Maps/Room.h"
#include <stdlib.h>

Monster::Monster(RenderContext& renderer,
	Player& p,
	Room* r,
	string textureId,
	int health,
	int dmg,
	int atkDelay,
	int atkRadius,
	int coins,
	int exp, int mvDelay, bool alarmed, int defense) :
	LivingEntity(health, coins, exp, defense),
	MovingEntity(0, 0, renderer, textureId),
	attackValue(dmg), player(p), room(r), attackDelay(atkDelay),
	attackRadius(atkRadius), alarmed(alarmed), moveDelay(mvDelay), alarmRadius(3),
	killed(false),
	type("") //No type yet
{
	texture = renderer.LoadTexture(textureId);
}

void Monster::kill()
{
	if (!killed)
	{
		player.gainExperience(experience);
		player.gainCoins(money);
		health = 0;
		killed = true;
	}
}

void Monster::tick(int time, GAME* game)
{
	if (!isAlive()) return;
	if (time - lastTimeAtk >= attackDelay)
	{
		lastTimeAtk = time;
		manageAlarm();
		attackRound();
	}
	if (time - lastTimeMv >= moveDelay)
	{
		room->tryTeleportAt(*this, x + GetRandom(3) - 1, y + GetRandom(3) - 1);
		lastTimeMv = time;
	}
}

void Monster::setRoom(Room* r)
{
	room = r;
}

void Monster::attackRound()
{
	if (abs(x - player.getX()) <= attackRadius && abs(y - player.getY()) <= attackRadius)
	{
		player.damage(attackValue);
	}
}

void Monster::manageAlarm()
{
	if (abs(x - player.getX()) <= alarmRadius && abs(y - player.getY()) <= alarmRadius)
	{
		alarmed = true;
	}
}

void Monster::render(RenderContext& renderer, int offsetX, int offsetY)const
{
	if (!isAlive()) return;
	int xx = (x + offsetX) * SZ_BLOCKSIZE;
	int yy = (y + offsetY) * SZ_BLOCKSIZE;
	texture->render(renderer, xx, yy, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
	drawHealthBar(renderer, xx, yy);
}

string Monster::monsterToString() const
{
	return isAlive() ? type + " " + to_string(health) : "";
}

void Monster::sendMonsterToWarp(int x, int y, int destRoom, int destX, int destY, bool playerJustLeft)
{
}

void Monster::cleanMonsterWarpInfo()
{
}
