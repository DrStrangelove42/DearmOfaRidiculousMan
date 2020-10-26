#include "Player.h"

Player::Player()
{
	texture = LoadTexture("mario");
}

void Player::damage(int dmg)
{

}

bool Player::isAlive()
{

}

void Player::render(SDL_Renderer renderer)
{
	DrawImage(renderer, texture, x * SZ_BLOCKSIZE, y * SZ_BLOCKSIZE, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
}