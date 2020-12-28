#include "Checkpoint.h"

Checkpoint::~Checkpoint()
{
}

Checkpoint::Checkpoint(string identifier, int posx, int posy, RenderContext& renderer) :
	Object(identifier, posx, posy, "empty", renderer, true)
{

}

bool Checkpoint::updateObject(GAME* game)
{
	return false;
}
