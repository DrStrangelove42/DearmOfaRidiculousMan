#include "Player.h"

Player::Player() {}

Player::Player(SDL_Renderer* renderer) : x(0), y(0)
{
	texture = LoadTexture("mario", renderer);
}

void Player::damage(int dmg)
{
	if (health - dmg >= 0)
		health -= dmg;
	else
		kill();
}

bool Player::isAlive()
{
	return health > 0;
}

void Player::teleport(int nx, int ny)
{
	x = nx;
	y = ny;
}

void Player::render(SDL_Renderer* renderer)
{
	DrawImage(renderer, texture, x * SZ_BLOCKSIZE, y * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
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