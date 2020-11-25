#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <functional>
#include "../Base/Texture.h"
#include "../Base/Entity.h"
#include "../Base/utils.h"

using namespace std;

class Label : public Entity
{
protected:
	Texture* texture;

	int x;
	int y;
public:
	Label(Texture* texture, int x, int y);

	Label(string caption, RenderContext& r, int x, int y, int color=0xffffffff);

	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	virtual void tick(int time, RenderContext&);
};

#endif