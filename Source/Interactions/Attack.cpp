#if false
#include "Attack.h"

Attack :: Attack (int startHealth, int startMoney, int startExp) : health(startHealth), maxHealth(startHealth), money(startMoney), experience(startExp)
{
	
}


void Attack :: attack(int damage, bool validAttack)
{
    if(validAttack)
    {
        setHealth(getHealth()-(attack-defense_));
    }
    else
    {
        setHealth(health_);
    }
}
#endif