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
