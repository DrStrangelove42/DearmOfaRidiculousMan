#include "Checkpoint.h"
#include "../Maps/Map.h"

Checkpoint::~Checkpoint()
{

}

Checkpoint::Checkpoint(string identifier, int posx, int posy, RenderContext& renderer) :
	Object(identifier, posx, posy, "checkflag", renderer, true)
{

}

bool Checkpoint::updateObject(GAME* game)
{
	if (x != game->player->getX() || y != game->player->getY())
	{
		return false;
	}
	//Enregistrer le contexte actuel
	game->currentMap->saveProgress(SAVES_CURRENT, game->worldName, *(game->currentMapId), game->currentMap->getCurrentRoom(), *(game->player));
	
	return true;
}

string Checkpoint::objectToString() const
{
	return id;
}
