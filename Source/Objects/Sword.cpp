#include "Sword.h"
#include "../Characters/Player.h"

Sword::Sword(string identifier, int posx, int posy, RenderContext& renderer, int attack) :
	PickableObject(identifier, posx, posy, "sword", renderer, true),
	VisibleWearable(renderer, "sword"), attack(attack)
{

}

int Sword::getAttack() const
{
	return attack;
}


Sword::Sword(string headerline, int posx, int posy, RenderContext& renderer) : Sword(EatToken(headerline), posx, posy, renderer, 10)
{
	try
	{
		attack = stoi(headerline);
	}
	catch (...)
	{
	}
}

string Sword::objectToString() const
{
	return id + " " + to_string(attack);
}

void Sword::equip(Player* p)
{
	VisibleWearable::equip(p);
	p->addAttack(attack);
}

void Sword::remove(Player* p)
{
	p->addAttack(-attack);
	VisibleWearable::remove(p);
}
 