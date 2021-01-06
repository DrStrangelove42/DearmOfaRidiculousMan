#include "Player.h"
#include "../Base/game.h"
#include "../Base/Window.h"
#include "../Maps/Room.h"
#include "../Maps/Map.h"
#include "../Objects/Object.h"
#include "../Maps/GameOverMenu.h"

#include "Monsters/Fireball.h"

Player::Player(RenderContext& renderer, int lives, int attack, int defense, int startHealth, int startMoney, int startExp) :
	LivingEntity(startHealth, startMoney, startExp, defense), MovingEntity(0, 0, renderer, "player"),
	lives(lives), attack(attack), infosX(SZ_MAINWIDTH), infosY(0),
	attackDelay(500), lastAttackTime(0), story(NULL)
{
	heart = renderer.LoadTexture("heart");
}

void Player::render(RenderContext& renderer, int offsetX, int offsetY)const
{
	int xx = (x + offsetX) * SZ_BLOCKSIZE;
	int yy = (y + offsetY) * SZ_BLOCKSIZE;
	loadedTx->render(renderer, xx, yy, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
	//DrawableEntity::render(renderer, offsetX, offsetY);
	drawHealthBar(renderer, xx, yy - 5);
	renderInventory(renderer, xx, yy);
}

bool Player::isAlive() const
{
	return lives > 0 || LivingEntity::isAlive();
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
	Texture* tmp = renderer.LoadString(to_string(experience) + " EXP", 0xCEB600FF);
	tmp->renderUnscaled(renderer, xx, yy);
	yy += tmp->getHeight();
	tmp = renderer.LoadString(to_string(money) + " Gold", 0xDDDD00FF);
	tmp->renderUnscaled(renderer, xx, yy);

	yy += tmp->getHeight() + SZ_BLOCKSIZE;

	tmp = renderer.LoadString("Collected stuff", 0xFFFFFFFF);
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
		health = 0;
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
		animateGameOver(time, game);
	}

	if (story != NULL)
	{
		story->tick(time, game);
	}
}

void Player::animateGameOver(int time, GAME* game)
{
	static int steps;
	static int i;
	static int j;
	static int s;
	static int t = 0;
	if (t == 0) {
		steps = 4 * max(game->currentMap->getCurrentRoomObject().getH(), game->currentMap->getCurrentRoomObject().getW());
		i = x;
		j = y;
		s = 1;
		for (int n = 0; n < game->currentMap->getRoomCount(); n++)
		{
			if (n != game->currentMap->getCurrentRoom())
			{
				game->currentMap->getRooms()[n]->setDiscovered(false);
			}
		}
	}

	if (t < steps)
	{
		switch (t % 4)
		{
		case 0://to the right
			for (int k = 0; k < s; k++)
			{
				i++;
				game->currentMap->getCurrentRoomObject().replaceBlock(new Block(i, j, "empty", *(game->renderer)));
			}
			break;
		case 1://downwards
			s++;
			for (int k = 0; k < s; k++)
			{
				j++;
				game->currentMap->getCurrentRoomObject().replaceBlock(new Block(i, j, "empty", *(game->renderer)));
			}
			break;
		case 2://to the left
			for (int k = 0; k < s; k++)
			{
				i--;
				game->currentMap->getCurrentRoomObject().replaceBlock(new Block(i, j, "empty", *(game->renderer)));
			}
			break;
		case 3://upwards
			s++;
			for (int k = 0; k < s; k++)
			{
				j--;
				game->currentMap->getCurrentRoomObject().replaceBlock(new Block(i, j, "empty", *(game->renderer)));
			}
			break;
		default:
			break;
		}
		t++;
	}
	else
	{
		t = 0;
		lives++;
		delete game->currentMap;
		*(game->currentMapId) = 0;
		game->worldName = "Game Over";
		game->currentMap = new GameOverMenu(*this, game);
	}
}

void Player::onKeyDown(GAME* game)
{
	if (!isAlive()) return;
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

	if (curX != x || curY != y)
		room.tryTeleportAt(*this, curX, curY);

	if (DEBUG_MODE)
		if (game->keyLetter == 'F')
			room.addMonster(new Fireball(*(game->renderer), *this, &room));

	if (story != NULL)
	{
		story->onKeyDown(game);
	}
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

void Player::gainExperience(int exp)
{
	experience += exp;
}

void Player::gainCoins(int n)
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



int Player::getLives()
{
	return lives;
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

void Player::setLives(int l)
{
	lives = l;
}

void Player::setStory(Story* s)
{
	if (story != NULL)
		clearStory();
	story = s;
}

void Player::clearStory()
{
	if (story != NULL)
		delete story;
	story = NULL;
}

Story& Player::getStory() const
{
	return *story;
}
