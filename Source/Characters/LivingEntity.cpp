#include "LivingEntity.h"

void LivingEntity::damage(int dmg)
{
	if (health - dmg >= 0)
		health -= dmg;
	else
		kill();
}

bool LivingEntity::isAlive()
{
	return health > 0;
}

/*
Game over if no lives left.
*/
void LivingEntity::kill()
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
