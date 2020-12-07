#include "Key.h"

Key::~Key()
{

}

Key::Key(string identifier, int posx, int posy, RenderContext& renderer) :
	Object(identifier, posx, posy, "key", renderer, true)
{

}

void Key::updateObject(GAME* game)
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
