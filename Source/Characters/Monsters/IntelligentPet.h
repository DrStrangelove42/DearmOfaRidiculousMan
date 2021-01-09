#ifndef INTELLIGENT_PET_H
#define INTELLIGENT_PET_H

#include "../IntelligentMonster.h"

/// <summary>
/// We create a type of monster : pet. These will always have the same characteristics.
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
