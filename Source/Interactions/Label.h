#ifndef LABEL_H
#define LABEL_H

#include <string>
#include <functional>
#include "../Base/Texture.h"
#include "../Characters/MovingEntity.h"
#include "../Base/utils.h"
#include "../Base/game.h"

using namespace std;

class Label : public MovingEntity
{
protected:
	/// <summary>
	/// 
	/// </summary>
	Texture* texture;
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	Label(Texture* texture, int x, int y);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="caption"></param>
	/// <param name="r"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="color"></param>
	Label(string caption, RenderContext& r, int x, int y, int color=0xffffffff);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="t"></param>
	void setTexture(Texture* t);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);
	virtual void tick(int time, GAME* game);
};

#endif
