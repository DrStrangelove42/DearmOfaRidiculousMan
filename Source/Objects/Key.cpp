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
	game->player->pickUpItem(Item(id, "key", renderer, 0, 0));
	texture = "empty";
	updateTexture(renderer);
}
