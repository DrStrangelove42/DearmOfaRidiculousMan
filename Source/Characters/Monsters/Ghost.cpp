#include "Ghost.h"

Ghost::Ghost(RenderContext& renderer, Player& p, Room* r) : Monster(renderer, p, r, "ghost", 50, 20)
{
	type = "g";
}

Ghost::~Ghost()
{

}
