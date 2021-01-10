#ifndef INTELLIGENT_PET_H
#define INTELLIGENT_PET_H

#include "../IntelligentMonster.h"

/// <summary>
/// An IntelligentPet is a MovingEntity that follows the Player without dealing damage.
/// </summary>
class IntelligentPet : public IntelligentMonster
{
protected:

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="p"></param>
	/// <param name="r"></param>
	IntelligentPet(RenderContext& renderer, Player& p, Room* r);
	~IntelligentPet();
};

#endif
