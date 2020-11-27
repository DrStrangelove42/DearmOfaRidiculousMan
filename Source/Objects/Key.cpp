#include "Key.h"

Key::~Key()
{

}

Key::Key(string identifier, int posx, int posy, Player& p, RenderContext& renderer) :
	Object(identifier, posx, posy, p, "key", renderer, true)
{

}

void Key::updateObject(Player& p, GAME* game)
{
	if (texture == "empty" || x != p.getX() || y != p.getY())
	{
		return;
	}
	RenderContext& renderer = *(game->renderer);
	p.pickUpItem(Item(id, "key", renderer, 0, 0));
	texture = "empty";
	updateTexture(renderer);
}
