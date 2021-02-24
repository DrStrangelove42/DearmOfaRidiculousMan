#include "VisibleWearable.h"


VisibleWearable::~VisibleWearable()
{
}

VisibleWearable::VisibleWearable(string identifier, int posx, int posy, string tag, RenderContext& renderer) :
	PickableObject(identifier, posx, posy, tag, renderer, true),
	renderer(renderer), tag(tag)
{

}

void VisibleWearable::equip(Player* p) const
{
	p->addObjectToWear(tag + "hand", this);
	p->setTextureTag(tag, true);
	p->updateTexture(renderer);
}

void VisibleWearable::remove(Player* p) const
{
	p->deleteWornObject(tag + "hand");
	//disable the tag
	p->setTextureTag(tag, false);
	p->updateTexture(renderer);
}

bool VisibleWearable::isWorn(Player* p) const
{
	return p->isWearingSomethingAt(tag + "hand", this);
}

void VisibleWearable::onPickup(Player* p) const
{
	if (!isWorn(p))
	{
		//we do not wear anything, so we automatically wear the object now
		p->wearObject(this);
	}
}
