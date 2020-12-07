#include "Player.h"
#include "../Maps/Room.h"
#include "../Maps/Map.h"
#include "../Objects/Object.h"

Player::Player(RenderContext& renderer, Window& main, int lives, int attack, int defense, int startHealth, int startMoney, int startExp) : LivingEntity(startHealth, startMoney, startExp), lives(lives), textureId("player"), attack(attack), defense(defense)
{
	texture = LoadTexture("player", renderer);
	infosWindow = new Window("Player informations", SZ_INFOSWIDTH, SZ_SCREENHEIGHT, main.getX() + main.getW(), main.getY());
	infosRenderer = new RenderContext(*infosWindow);
	heart = LoadTexture("heart", *infosRenderer);
}

void Player::render(RenderContext& renderer, int offsetX, int offsetY)
{
	int xx = (x + offsetX) * SZ_BLOCKSIZE;
	int yy = (y + offsetY) * SZ_BLOCKSIZE;
	texture->render(renderer, xx, yy, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
	drawHealthBar(renderer, xx, yy);

	infosRenderer->clear();
	xx = 0;
	yy = 0;

	for (int i = 0; i < lives; i++)
	{
		if (xx >= SZ_INFOSWIDTH)
		{
			xx = 0;
			yy += heart->getHeight();
		}
		heart->renderUnscaled(*infosRenderer, xx, yy);
		xx += heart->getWidth();
	}
	yy += heart->getHeight();
	xx = 0;
	Texture* tmp = LoadString(to_string(experience) + " EXP", *infosRenderer, 0xCEB600FF);
	tmp->renderUnscaled(*infosRenderer, xx, yy);
	yy += tmp->getHeight();
	tmp = LoadString(to_string(money) + " Gold", *infosRenderer, 0xDDDD00FF);
	tmp->renderUnscaled(*infosRenderer, xx, yy);
	infosRenderer->update();
}

/*
Game over if no lives left.
*/
void Player::kill()
{
	if (lives == 0)
	{
		// TODO gameover ?
	}
	else
	{
		lives--;
		health = maxHealth;
	}
}

void Player::updateTexture(RenderContext& renderer)
{
	texture = LoadTexture(textureId, renderer);
}

Player::~Player()
{
	delete infosRenderer;
	delete infosWindow;
}

void Player::tick(int time, GAME* game)
{

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
	for (Monster* m : room.getMonsters())
	{
		if (isInAttackRange(m->getX(), m->getY()))
		{
			m->damage(attack);
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

void Player::pickUpObject(Object obj, int count)
{
	if (inventory.find(obj.getId()) == inventory.end())
	{
		inventory[obj.getId()] = count;
		attack = max(obj.getAttack(), attack);
		defense = max(obj.getDefense(), defense);
	}
	else
	{
		inventory[obj.getId()] += count;
	}
}

bool Player::hasObject(string objId)
{
	return (inventory.find(objId) != inventory.end() && inventory[objId] > 0);
}

bool Player::hasObject(Object obj)
{
	return (inventory.find(obj.getId()) != inventory.end() && inventory[obj.getId()] > 0);
}
