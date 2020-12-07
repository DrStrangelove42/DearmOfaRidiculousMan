#include "Sword.h"

Sword::Sword(string identifier, int posx, int posy, RenderContext& renderer, int attack) : Object(identifier, posx, posy, "key" /*To be changed if we want to show the sword on screen in an inventory for example. */,	renderer, attack, 0)
{

}

Sword::~Sword()
{

}

void Sword::updateObject(GAME* game)
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
