#include "Fireball.h"

Fireball::Fireball(RenderContext& renderer, Player& p, Room* r) : IntelligentMonster(renderer, p, r, "*fireball", 400, 40, 500)
{
	((AnimatedTexture*)texture)->setDelay(250);
	type = "F";
}


Fireball::~Fireball()
{

}
