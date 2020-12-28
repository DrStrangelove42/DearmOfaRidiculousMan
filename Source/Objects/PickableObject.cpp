#include "PickableObject.h"
#include "../Characters/Player.h"
#include "../Maps/Map.h"

PickableObject::~PickableObject()
{

}

PickableObject::PickableObject(string identifier, int posx, int posy, string tx, RenderContext& renderer, bool trav, int attack, int defense):
	Object(identifier, posx, posy, tx, renderer, trav, attack,defense)
{
}

bool PickableObject::updateObject(GAME* game)
{
	if (x != game->player->getX() || y != game->player->getY())
	{
		return false;
	}

	RenderContext& renderer = *(game->renderer);
	game->player->pickUpObject(this);
	/*Delete the pointer from the room*/
	return true;
}
