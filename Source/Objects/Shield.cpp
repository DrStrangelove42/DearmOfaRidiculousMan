#include "Shield.h"
#include "../Characters/Player.h"
Shield::Shield(string identifier, int posx, int posy, RenderContext& renderer, int defense) : PickableObject(identifier, posx, posy, "shield", renderer, true, 0, defense)
{

} 

string Shield::objectToString() const
{
	return id + " " + to_string(defense);
}
