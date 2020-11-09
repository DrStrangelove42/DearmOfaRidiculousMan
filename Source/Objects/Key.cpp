#include "Key.h"

Key::~Key()
{

}

Key::Key(char identifier, int posx, int posy, Player& p, RenderContext& renderer) : Object(posx, posy, p, "key", renderer), id(identifier)
{

}

char Key::getId()
{
	return id;
}

void Key::updateObject(Player& p, RenderContext& renderer)
{
  
}
