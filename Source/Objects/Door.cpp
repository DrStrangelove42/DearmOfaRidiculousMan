#include "Door.h"

Door::~Door()
{

}

Door::Door(string identifier, int posx, int posy, Player& p, RenderContext& renderer) : Object(identifier, posx, posy, p, "door", renderer, false)
{

}

void Door::updateObject(Player& p, RenderContext& renderer, EVENT_ARGS* ea) {

	//TODO if player is within one block and has corresponding key in inventory, and door is closed, open it. Note that door is closed iff traversable = false 
}
