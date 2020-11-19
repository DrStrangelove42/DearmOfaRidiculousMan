#include "Player.h"

Player::Player(RenderContext& renderer, int lives, int startHealth, int startMoney, int startExp) : lives(lives), LivingEntity(startHealth, startMoney, startExp)
{
	texture = LoadTexture("mario", renderer);
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

void Player::tick(int time)
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

void Player::pickUpItem(Item item)
{
        if (items.find(item.getId()) == items.end())
	{
	        items[item.getId()] = 1;
	}
	else
	{
	        items[item.getId()] += 1;
	}
}

bool Player::hasItem(string itemid)
{
        return (items.find(itemid) != items.end() && items[itemid]>0);
}

bool Player::hasItem(Item item)
{
        return (items.find(item.getId()) != items.end() && items[item.getId()]>0);
}
