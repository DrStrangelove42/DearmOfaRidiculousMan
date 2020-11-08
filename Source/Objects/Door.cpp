#include "Door.h"

Door::Door(char identifier, int posx, int posy, Player& p, RenderContext& renderer) : Object(posx, posy, p, "door", renderer), id(identifier)
{

}

char Door::getId()
{
  return id;
}
