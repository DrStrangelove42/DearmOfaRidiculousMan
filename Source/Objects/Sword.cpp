#include "Sword.h"
#include "../Characters/Player.h"
Sword::Sword(string identifier, int posx, int posy, RenderContext& renderer, int attack) : PickableObject(identifier, posx, posy, "playersword" /*To be changed if we want to show the sword on screen in an inventory for example. */,	renderer, attack, 0)
{

} 