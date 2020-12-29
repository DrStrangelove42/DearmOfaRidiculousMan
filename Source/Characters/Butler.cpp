#include "Butler.h"
#include "Player.h"

Butler::Butler(string name, string greeting, int posx, int posy, RenderContext& renderer) :
	NPC(name, greeting, posx, posy, "butler", renderer, true)
{

}

Butler::Butler(string headerline, int posx, int posy, RenderContext& renderer) :
	Butler(NextToken(headerline, ' '), "", posx, posy, renderer)
{
	//todo
}

bool Butler::updateObject(GAME* game)
{
	return false;
}
