#ifndef INTELLIGENT_SKELETON_H
#define INTELLIGENT_SKELETON_H

#include "../IntelligentMonster.h"

/// <summary>
/// An IntelligentSkeleton is a type of Monster that is the same as a Skeleton, except that it follows the Player.
/// </summary>
class IntelligentSkeleton : public IntelligentMonster
{
protected:

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="p"></param>
	/// <param name="r"></param>
	IntelligentSkeleton(RenderContext& renderer, Player& p, Room* r);
	~IntelligentSkeleton();
};

#endif
