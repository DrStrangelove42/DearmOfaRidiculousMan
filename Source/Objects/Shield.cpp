#include "Shield.h"
#include "../Characters/Player.h"
Shield::Shield(string identifier, int posx, int posy, RenderContext& renderer, int defense) : PickableObject(identifier, posx, posy, "playershield" /*To be changed if we want to show the shield on screen in an inventory for example. */, renderer, true, 0, defense)
{

} 

string Shield::objectToString()
{
	return "sh " + to_string(defense);
}
