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
	int exp, int mvDelay, bool alarmed) :
	LivingEntity(health, coins, exp), MovingEntity(0, 0, renderer, textureId), attackValue(dmg), player(p), room(r), attackDelay(atkDelay), attackRadius(atkRadius), alarmed(alarmed), moveDelay(mvDelay), alarmRadius(3)
{
	texture = renderer.LoadTexture(textureId);
}

void Monster::kill()
{
	if (health == -1)
	        return;
	health = -1;
	player.getExperience(experience);
	player.getCoins(money);
	//room.removeMonster(this);
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

		/*switch (r)
		{
		case 0:
			room.tryTeleportAt(*m, x + 1, y); break;
		case 1:
			room.tryTeleportAt(*m, x, y + 1); break;
		case 2:
			room.tryTeleportAt(*m, x - 1, y); break;
		case 3:
			room.tryTeleportAt(*m, x, y - 1); break;
		default:
			break;
		}*/
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
