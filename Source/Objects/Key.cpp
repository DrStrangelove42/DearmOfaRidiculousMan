#include "Key.h"

Key::~Key()
{

}

Key::Key(char identifier, int posx, int posy, Player& p, RenderContext& renderer) : 
    Object(posx, posy, p, "key", renderer, true), id(identifier)
{

}

char Key::getId()
{
	return id;
}

void Key::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea)
{
  if (x == p.getX() && y == p.getY()){
      //TODO turn key into item and give to player
    }
}
