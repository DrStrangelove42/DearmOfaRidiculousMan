#include "RenderContext.h"

using namespace std;

RenderContext::RenderContext(SDL_Window* window)
{
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (NULL == renderer)
	{
		throw runtime_error(SDL_GetError());
	}
}

RenderContext::~RenderContext()
{
	if (NULL != renderer)
		SDL_DestroyRenderer(renderer);
}

void RenderContext::clear()
{
	changeColor(0x000000ff);
	SDL_RenderClear(renderer);
}

void RenderContext::doRender(SDL_Texture* t,
	const SDL_Rect* srcrect,
	const SDL_Rect* dstrect,
	const double angle,
	const SDL_Point* center,
	const SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, t, srcrect, dstrect, angle, center, flip);
}

void RenderContext::update()
{
	SDL_RenderPresent(renderer);
}

SDL_Texture* RenderContext::fromSurface(SDL_Surface* s)
{
	return SDL_CreateTextureFromSurface(renderer, s);
}

void RenderContext::changeColor(int color)
{
	if (0 != SDL_SetRenderDrawColor(renderer, (unsigned char)(color & 0xff000000),
		(unsigned char)(color & 0x00ff0000),
		(unsigned char)(color & 0x0000ff00),
		(unsigned char)(color & 0x000000ff)))
		throw runtime_error(SDL_GetError());
}

void RenderContext::drawRectangle(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderDrawRect(renderer, &rect);
}

void RenderContext::drawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}