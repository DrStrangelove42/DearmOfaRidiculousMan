#include "OpenDoor.h"

OpenDoor::~OpenDoor()
{

}

OpenDoor::OpenDoor(char identifier, int posx, int posy, Player& p, RenderContext& renderer) : Object(posx, posy, p, "door", renderer, true), id(identifier)
{

}

char OpenDoor::getId()
{
	return id;
}

void OpenDoor::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea){

}
