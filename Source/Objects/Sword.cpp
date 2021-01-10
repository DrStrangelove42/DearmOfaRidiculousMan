#include "Sword.h"
#include "../Characters/Player.h"
Sword::Sword(string identifier, int posx, int posy, RenderContext& renderer, int attack) : PickableObject(identifier, posx, posy, "sword", renderer, attack, 0)
{

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
