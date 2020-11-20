#include "Player.h"

Player::Player(RenderContext& renderer, int lives, int attack, int defense, int startHealth, int startMoney, int startExp) : lives(lives), textureId("player"), LivingEntity(startHealth, startMoney, startExp)
{
	texture = LoadTexture("player", renderer);
}

void Player::render(RenderContext& renderer, int offsetX, int offsetY)
{
	int xx = (x + offsetX) * SZ_BLOCKSIZE;
	int yy = (y + offsetY) * SZ_BLOCKSIZE;
	texture->render(renderer, xx, yy, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
	drawHealthBar(renderer, xx, yy);
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

void Player::tick(int time, RenderContext& r)
{

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

void Player::pickUpItem(Item item, int count)
{
	if (items.find(item.getId()) == items.end())
	{
		items[item.getId()] = count;
		attack = max(item.getAttack(), attack);
		defense = max(item.getDefense(), defense);
	}
	else
	{
		items[item.getId()] += count;
	}
}

bool Player::hasItem(string itemid)
{
	return (items.find(itemid) != items.end() && items[itemid] > 0);
}

bool Player::hasItem(Item item)
{
	return (items.find(item.getId()) != items.end() && items[item.getId()] > 0);
}
