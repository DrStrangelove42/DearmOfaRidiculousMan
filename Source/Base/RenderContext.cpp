#include "RenderContext.h"

RenderContext::RenderContext()
{

}

RenderContext::~RenderContext()
{
    SDL_DestroyRenderer(renderer);
}

RenderContext::doRender(SDL_Texture * t, 
    SDL_Texture* texture,
    const SDL_Rect* srcrect,
    const SDL_Rect* dstrect,
    const double           angle,
    const SDL_Point* center,
    const SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, t, srcrect, dstrect, angle, center, flip);
}