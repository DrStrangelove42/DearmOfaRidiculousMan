#include "Sword.h"

Sword::Sword(string identifier, RenderContext& renderer, int attack) : Item(identifier, 
	"key" /*To be changed if we want to show the sword on screen in an inventory for example. */, 
	renderer, 
	attack, 
	0)
{

}

Sword::~Sword()
{

}
