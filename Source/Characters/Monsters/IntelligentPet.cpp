#include "IntelligentPet.h"

IntelligentPet::IntelligentPet(RenderContext& renderer, Player& p, Room* r) : IntelligentMonster(renderer, p, r, "pet", 80, 0)
{
	type = "P";
}


IntelligentPet::~IntelligentPet()
{

}
