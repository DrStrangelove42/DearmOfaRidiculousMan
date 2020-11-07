#ifndef RENDERCTXT_H
#define RENDERCTXT_H

#include <SDL2/SDL.h>
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
 
    int clear();
    void update();

    SDL_Texture* fromSurface(SDL_Surface*);

    int doRender(SDL_Texture* t,
        const SDL_Rect* srcrect,
        const SDL_Rect* dstrect,
        const double           angle,
        const SDL_Point* center,
        const SDL_RendererFlip flip);


};

#endif