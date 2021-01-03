#ifndef INTELLIGENT_GHOST_H
#define INTELLIGENT_GHOST_H

#include "../IntelligentMonster.h"

/// <summary>
/// We create a type of monster which are the same as ghosts, but are intelligent (they move towards the player).
/// </summary>
class IntelligentGhost : public IntelligentMonster
{
protected:

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="p"></param>
	/// <param name="r"></param>
	IntelligentGhost(RenderContext& renderer, Player& p, Room* r);
	~IntelligentGhost();
};

#endif
