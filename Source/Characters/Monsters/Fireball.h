#ifndef FIREBALL_H
#define FIREBALL_H

#include "../IntelligentMonster.h"

/// <summary>
/// A fireball. These will always have the same characteristics.
/// </summary>
class Fireball : public IntelligentMonster
{
protected:

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="p"></param>
	/// <param name="r"></param>
	Fireball(RenderContext& renderer, Player& p, Room& r);
	~Fireball();
};

#endif
