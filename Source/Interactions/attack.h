//this file defines the attack interaction
#ifndef ATTACK_H
#define ATTACK_H

#include <string>


void Charactor::attack(int damage, bool validAttack)
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
