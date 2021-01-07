#include "Butler.h"
#include "Player.h"

Butler::Butler(string name, string greeting, int posx, int posy, RenderContext& renderer) :
	NPC(name,name, greeting, posx, posy, "butler", renderer, NULL, true)//No need for a map, because we do not have any button
{
	//We do not sign in for any mouse event.
	signedInForEvents = true;
}



Butler::Butler(string headerline, int posx, int posy, RenderContext& renderer) :
	Butler(EatToken(headerline), "", posx, posy, renderer)
{
	name = EatToken(headerline);
	speech = headerline;
	setTexture(renderer);
}

bool Butler::updateObject(GAME* game)
{
	return NPC::updateObject(game);
}
