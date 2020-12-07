#include "Shield.h"

Shield::Shield(string identifier, int posx, int posy, RenderContext& renderer, int defense) : Object(identifier, posx, posy, "key" /*To be changed if we want to show the shield on screen in an inventory for example. */, renderer, true, 0, defense)
{

}

Shield::~Shield()
{

}

void Shield::updateObject(GAME* game)
{
	if (texture == "empty" || x != game->player->getX() || y != game->player->getY())
	{
		return;
	}
	RenderContext& renderer = *(game->renderer);
	game->player->pickUpObject(*this);
	texture = "empty";
	updateTexture(renderer);
}
