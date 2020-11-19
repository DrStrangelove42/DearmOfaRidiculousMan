#include "Shield.h"

Shield::Shield(string identifier, RenderContext& renderer, int attack=10) : Item(identifier, "key" /*To be changed if we want to show the shield on screen in an inventory for example. */, renderer, 0, defense)
{

}

Shield::~Shield()
{

}
