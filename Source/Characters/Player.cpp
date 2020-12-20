#include "Player.h"
#include "../Base/game.h"
#include "../Base/Window.h"
#include "../Maps/Room.h"
#include "../Maps/Map.h"
#include "../Objects/Object.h"
#include "../Maps/GameOverMenu.h"

Player::Player(RenderContext& renderer, int lives, int attack, int defense, int startHealth, int startMoney, int startExp) :
	LivingEntity(startHealth, startMoney, startExp), MovingEntity(0, 0, renderer, "player"),
	lives(lives), attack(attack), defense(defense), infosX(SZ_MAINWIDTH), infosY(0), attackDelay(500), lastAttackTime(0)
{
	heart = LoadTexture("heart", renderer);
}

void Player::render(RenderContext& renderer, int offsetX, int offsetY)const
{
	int xx = (x + offsetX) * SZ_BLOCKSIZE;
	int yy = (y + offsetY) * SZ_BLOCKSIZE;
	loadedTx->render(renderer, xx, yy, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
	//DrawableEntity::render(renderer, offsetX, offsetY);
	drawHealthBar(renderer, xx, yy);
	renderInventory(renderer, xx, yy);
}

void Player::renderInventory(RenderContext& renderer, int xx, int yy)const
{
	/*Infos*/
	xx = infosX;
	yy = infosY;

	for (int i = 0; i < lives; i++)
	{
		if (xx >= infosX + SZ_INFOSWIDTH)
		{
			xx = infosX;
			yy += heart->getHeight();
		}
		heart->renderUnscaled(renderer, xx, yy);
		xx += heart->getWidth();
	}

	yy += heart->getHeight();
	xx = infosX;
	Texture* tmp = LoadString(to_string(experience) + " EXP", renderer, 0xCEB600FF);
	tmp->renderUnscaled(renderer, xx, yy);
	yy += tmp->getHeight();
	tmp = LoadString(to_string(money) + " Gold", renderer, 0xDDDD00FF);
	tmp->renderUnscaled(renderer, xx, yy);

	yy += tmp->getHeight() + SZ_BLOCKSIZE;

	tmp = LoadString("Collected stuff", renderer, 0xFFFFFFFF);
	tmp->renderUnscaled(renderer, xx, yy);

	xx = infosX;
	yy += tmp->getHeight();
	/*The inventory*/
	for (auto& entry : inventoryLookup)
	{
		entry.second->sideRender(renderer, xx, yy);
		xx += SZ_BLOCKSIZE;
		if (xx >= infosX + SZ_INFOSWIDTH)
		{
			xx = infosX;
			yy += SZ_BLOCKSIZE;
		}
	}
}

/*
Game over if no lives left.
*/
void Player::kill()
{
	if (lives == 0)
	{

	}
	else
	{
		lives--;
		health = maxHealth;
	}
}

Player::~Player()
{
	inventory.clear();
	inventoryLookup.clear();
}

void Player::tick(int time, GAME* game)
{
	if (lives == 0 && !isAlive())
	{
		delete game->currentMap;
		game->currentMap = new GameOverMenu(*this, game);
	}
}

void Player::onKeyDown(GAME* game)
{
	Room& room = game->currentMap->getCurrentRoomObject();

	int curX = x;
	int curY = y;

	switch (game->key)
	{

	case Up:
		curY--;
		break;
	case Left:
		curX--;
		break;
	case Right:
		curX++;
		break;
	case Down:
		curY++;
		break;
	case A:
		//TODO Jump ?
		break;
	case B:
		//Atk
		attackMonsters(room);
		break;
	default:
		break;
	}
	if (DEBUG_MODE)
		if (game->keyLetter == 'M')
			room.addMonster(new Ghost(*(game->renderer), *this, room));

	if (curX != x || curY != y)
		room.tryTeleportAt(*this, curX, curY);
}


void Player::attackMonsters(Room& room)
{
	int t = GetTime();
	if (t - lastAttackTime >= attackDelay)
	{
		lastAttackTime = GetTime();
		for (Monster* m : room.getMonsters())
		{
			if (isInAttackRange(m->getX(), m->getY()))
			{
				m->damage(attack);
			}
		}
	}
}

void Player::getExperience(int exp)
{
	experience += exp;
}

void Player::getCoins(int n)
{
	money += n;
}

bool Player::isInAttackRange(int mx, int my)
{
	return abs(x - mx) < 2 && abs(y - my) < 2;
}

int Player::getAttack()
{
	return attack;
}

int Player::getDefense()
{
	return defense;
}

void Player::pickUpObject(const Object* obj, int count)
{
	if (inventory.find(obj->getId()) == inventory.end())
	{
		inventory[obj->getId()] = 0;
		attack = max(obj->getAttack(), attack);
		defense = max(obj->getDefense(), defense);
	}

	inventory[obj->getId()] += count;

	inventoryLookup[obj->getId()] = const_cast<Object*>(obj); //C++ is fairly annoying too
}

bool Player::hasObject(string objId)
{
	return (inventory.find(objId) != inventory.end() && inventory[objId] > 0);
}

bool Player::hasObject(Object obj)
{
	return (inventory.find(obj.getId()) != inventory.end() && inventory[obj.getId()] > 0);
}
