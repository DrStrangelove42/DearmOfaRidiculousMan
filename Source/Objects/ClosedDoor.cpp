#include "ClosedDoor.h"

ClosedDoor::~ClosedDoor()
{

}

ClosedDoor::ClosedDoor(char identifier, int posx, int posy, Player& p, RenderContext& renderer) : Object(posx, posy, p, "door", renderer, false), id(identifier)
{

}

char ClosedDoor::getId()
{
	return id;
}

void ClosedDoor::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea){
  
  //TODO if player is within one block and has corresponding key in inventory, replace ClosedDoor with OpenDoor
}
