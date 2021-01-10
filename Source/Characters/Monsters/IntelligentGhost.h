#ifndef INTELLIGENT_GHOST_H
#define INTELLIGENT_GHOST_H

#include "../IntelligentMonster.h"

/// <summary>
/// An IntelligentGhost is a type of Monster that is the same as a Ghost, except that it follows the Player.
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
