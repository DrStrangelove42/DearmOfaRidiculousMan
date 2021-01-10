#ifndef GHOST_H
#define GHOST_H

#include "../Monster.h"

/// <summary>
/// A Ghost is a type of Monster. These will always have the same characteristics.
/// </summary>
class Ghost : public Monster
{
protected:

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="p"></param>
	/// <param name="r"></param>
	Ghost(RenderContext& renderer, Player& p, Room* r);
	~Ghost();
};

#endif
