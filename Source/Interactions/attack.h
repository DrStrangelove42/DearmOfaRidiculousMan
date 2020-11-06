//this file defines the attack interaction


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
