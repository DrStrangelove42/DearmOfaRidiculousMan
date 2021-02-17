#ifndef VWEARABLE_H
#define VWEARABLE_H

#include "Wearable.h"

/// <summary>
/// 
/// </summary>
class VisibleWearable : public Wearable
{
protected:
	RenderContext& renderer;
	string tag;
public:
	virtual ~VisibleWearable();
	 
	VisibleWearable(RenderContext& r, string tag);
	virtual void equip(Player* p);
	virtual void remove(Player* p);

	/// <summary>
	/// Called when the object is picked up.
	/// </summary>
	virtual void onPickup(Player* p);
};

#endif
