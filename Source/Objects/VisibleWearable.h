#ifndef VWEARABLE_H
#define VWEARABLE_H

#include "Wearable.h"
#include "PickableObject.h"

/// <summary>
/// 
/// </summary>
class VisibleWearable : public Wearable, public PickableObject
{
protected:
	RenderContext& renderer;
	string tag;
public:
	virtual ~VisibleWearable();

	VisibleWearable(string identifier, int posx, int posy, string tag, RenderContext& renderer);
	virtual void equip(Player* p)const;
	virtual void remove(Player* p)const;

	/// <summary>
	/// Called when the object is picked up.
	/// </summary>
	virtual void onPickup(Player* p) const;
};

#endif
