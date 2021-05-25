#include "PickableObject.h"
#include "../Characters/Player.h"
#include "../Maps/Map.h"

PickableObject::~PickableObject()
{

}

PickableObject::PickableObject(const PickableObject& other) :Object(other)
{

}

PickableObject::PickableObject(string identifier, int posx, int posy, string tx, RenderContext& renderer, bool trav) :
	Object(identifier, posx, posy, tx, renderer, trav, "", true)
{
}

bool PickableObject::updateObject(GAME* game)
{
	if (x != game->player->getX() || y != game->player->getY())
	{
		return false;
	}

	game->player->pickUpObject(this);
	/*Delete the pointer from the room*/
	return true;
}

void PickableObject::onPickup(Player* p) const
{
	/*Do nothing, but we do not want this class to be abstract*/
}

