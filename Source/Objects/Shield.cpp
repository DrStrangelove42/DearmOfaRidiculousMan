#include "Shield.h"
#include "../Characters/Player.h"
Shield::Shield(string identifier, int posx, int posy, RenderContext& renderer, int defense) :
	VisibleWearable(identifier, posx, posy, "shield", renderer), defense(defense)
{
	info = "A shield made of wood and iron, that will protect you from most enemies.";
}


int Shield::getDefense() const
{
	return defense;
}

Shield::Shield(string headerline, int posx, int posy, RenderContext& renderer) : Shield(EatToken(headerline), posx, posy, renderer, 10)
{
	try
	{
		defense = stoi(headerline);
	}
	catch (...)
	{
	}
}

string Shield::objectToString() const
{
	return id + " " + to_string(defense);
}

void Shield::equip(Player* p) const
{
	VisibleWearable::equip(p);
	p->addDefense(defense);
}

void Shield::remove(Player* p) const
{
	p->addDefense(-defense);
	VisibleWearable::remove(p);
}

string Shield::getInfo() const
{
	return info + "\n\nDefense value " + to_string(defense);
}
