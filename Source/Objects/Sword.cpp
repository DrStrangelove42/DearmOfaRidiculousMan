#include "Sword.h"
#include "../Characters/Player.h"
Sword::Sword(string identifier, int posx, int posy, RenderContext& renderer, int attack) : PickableObject(identifier, posx, posy, "sword", renderer, attack, 0)
{

}

string Sword::objectToString()
{
	return "sw " + to_string(attack);
}
