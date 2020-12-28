#include "Signboard.h"

Signboard::~Signboard()
{
}

Signboard::Signboard(string identifier, int posx, int posy, RenderContext& renderer) :
	Object(identifier, posx, posy, "signboard", renderer, true)
{

}

bool Signboard::updateObject(GAME* game)
{
	return false;
}
