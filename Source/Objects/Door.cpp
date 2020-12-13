#include "Door.h"
#include "../Characters/Player.h"
Door::~Door()
{

}

Door::Door(string keyId, string openOrientation, string closedOrientation, string identifier, int posx, int posy, RenderContext& renderer) : keyId(keyId), openOrientation(openOrientation), closedOrientation(closedOrientation), Object(identifier, posx, posy, "door" + closedOrientation, renderer, false)
{

}

Door::Door(string headerline, int posx, int posy, RenderContext& renderer) : Door(headerline.substr(3,1), headerline.substr(7,1), headerline.substr(5,1),headerline.substr(0,2), posx, posy, renderer)
{

}

void Door::updateObject(GAME* game)
{
	if (traversable || abs(x - game->player->getX()) + abs(y - game->player->getY()) > 1)
	{
		return;
	}
	if (game->player->hasObject("k" + keyId))
	{
		traversable = true;
		texture = "door" + openOrientation;
		updateTexture(*(game->renderer));
	}
}
