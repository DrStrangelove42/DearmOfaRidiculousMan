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

int RenderContext::clear()
{
	SDL_RenderClear(renderer);
}

int RenderContext::doRender(SDL_Texture* t,
	const SDL_Rect* srcrect,
	const SDL_Rect* dstrect,
	const double           angle,
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