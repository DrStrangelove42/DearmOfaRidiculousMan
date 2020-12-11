#ifndef INTELLIGENT_SKELETON_H
#define INTELLIGENT_SKELETON_H

#include "../IntelligentMonster.h"

/// <summary>
/// We create a type of monster : skeletons. These will always have the same characteristics.
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
	IntelligentSkeleton(RenderContext& renderer, Player& p, Room& r);
	~IntelligentSkeleton();
};

#endif
