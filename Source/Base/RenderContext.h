#ifndef RENDERCTXT_H
#define RENDERCTXT_H

#include "utilsSDL.h"
#include <stdexcept>

/*
A class encapsulating a rendering context.
*/
class RenderContext
{
protected:
	/// <summary>
	/// The native renderer.
	/// </summary>
	SDL_Renderer* renderer;
public:
	/// <summary>
	/// Creates a new render context from the specified window.
	/// </summary>
	/// <param name="window"></param>
	RenderContext(Window& window);
	~RenderContext();

	/// <summary>
	/// Erases the entire canevas.
	/// </summary>
	void clear();

	/// <summary>
	/// Flushes the graphical modifications to appear on the screen.
	/// </summary>
	void update();

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	SDL_Texture* fromSurface(SDL_Surface*);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t"></param>
	/// <param name="srcrect"></param>
	/// <param name="dstrect"></param>
	/// <param name="angle"></param>
	/// <param name="center"></param>
	/// <param name="flip"></param>
	void doRender(SDL_Texture* t,
		const SDL_Rect* srcrect,
		const SDL_Rect* dstrect,
		const double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="fill"></param>
	void drawRectangle(int x, int y, int w, int h, bool fill = false);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	void drawLine(int x1, int y1, int x2, int y2);

	/// <summary>
	/// Sets the current color, in the format 0xRRGGBBAA 
	/// </summary>
	/// <param name="color"></param>
	void changeColor(int color);
};

#endif