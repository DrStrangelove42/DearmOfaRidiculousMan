#include "VisibleWearable.h"

VisibleWearable::~VisibleWearable()
{
}

VisibleWearable::VisibleWearable(RenderContext& r, string tag) : renderer(r), tag(tag)
{

}

void VisibleWearable::equip(Player* p)
{
	p->addObjectToWear(tag + "hand", this);
	p->setTextureTag(tag, true);
	p->updateTexture(renderer);
}

void VisibleWearable::remove(Player* p)
{
	p->deleteWornObject(tag + "hand");
	//disable the tag
	p->setTextureTag(tag, false);
	p->updateTexture(renderer);
}

void VisibleWearable::onPickup(Player* p)
{
	if (p->isWearingSomethingAt(tag + "hand"))
	{
		//we do not wear anything, so we automatically wear the object now
		p->wearObject(this);
	}
}
