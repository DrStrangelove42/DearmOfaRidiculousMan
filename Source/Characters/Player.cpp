#include "Player.h"

Player::Player(RenderContext& renderer)
{
	texture = LoadTexture("mario", renderer);
}

void Player::render(RenderContext& renderer, int offsetX, int offsetY)
{
	texture->render(renderer, (x + offsetX) * SZ_BLOCKSIZE, (y + offsetY) * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
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
