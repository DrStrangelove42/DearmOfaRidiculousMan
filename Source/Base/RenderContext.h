#ifndef RENDERCTXT_H
#define RENDERCTXT_H

#include "rendering.h"
#include <stdexcept>

/*
A class encapsulating a rendering context.
*/
class RenderContext
{
private:
	SDL_Renderer* renderer;
public:
	RenderContext(SDL_Window* window);
	~RenderContext();

	void clear();
	void update();

	SDL_Texture* fromSurface(SDL_Surface*);

	void doRender(SDL_Texture* t,
		const SDL_Rect* srcrect,
		const SDL_Rect* dstrect,
		const double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip);

	void drawRectangle(int x, int y, int w, int h, bool fill = false);
	void drawLine(int x1, int y1, int x2, int y2);

	/* Sets the current color, in the format 0xRRGGBBAA */
	void changeColor(int color);
};

#endif