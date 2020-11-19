#include "Player.h"

Player::Player(RenderContext& renderer)
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