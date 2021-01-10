#ifndef SKELETON_H
#define SKELETON_H

#include "../Monster.h"

/// <summary>
/// A Skeleton is a type of Monster. These will always have the same characteristics.
/// </summary>
class Skeleton : public Monster
{
protected:

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="p"></param>
	/// <param name="r"></param>
	Skeleton(RenderContext& renderer, Player& p, Room* r);
	~Skeleton();
};

#endif
