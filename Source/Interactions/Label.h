#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <functional>
#include "../Base/Texture.h"
#include "../Characters/MovingEntity.h"
#include "../Base/utils.h"

using namespace std;

class Label : public MovingEntity
{
protected:
	Texture* texture;
public:
	Label(Texture* texture, int x, int y);

	Label(string caption, RenderContext& r, int x, int y, int color=0xffffffff);

	void setTexture(Texture* t);

	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	virtual void tick(int time, RenderContext&);
};

#endif