#ifndef SKELETON_H
#define SKELETON_H

#include "../Monster.h"

/*
We create a type of monster : skeletons. These will always have the same characteristics.
*/
class Skeleton : public Monster
{
protected:

public:
	Skeleton(RenderContext& renderer, Player& p, Room& r);
	~Skeleton();
};

#endif
