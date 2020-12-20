#include "Shield.h"
#include "../Characters/Player.h"
Shield::Shield(string identifier, int posx, int posy, RenderContext& renderer, int defense) : PickableObject(identifier, posx, posy, "key" /*To be changed if we want to show the shield on screen in an inventory for example. */, renderer, true, 0, defense)
{

} 
