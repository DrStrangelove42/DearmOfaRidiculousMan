#include "Skeleton.h"

Skeleton::Skeleton(RenderContext& renderer, Player& p, Room* r) : Monster(renderer, p, r, "skeleton", 80, 10, 2000)
{
	type = "s";
}


Skeleton::~Skeleton()
{

}
