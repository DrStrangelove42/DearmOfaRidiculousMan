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
 
    void clear();
    void update();

    SDL_Texture* fromSurface(SDL_Surface*);

    void doRender(SDL_Texture* t,
        const SDL_Rect* srcrect,
        const SDL_Rect* dstrect,
        const double angle,
        const SDL_Point* center,
        const SDL_RendererFlip flip);

    void drawRectangle(int x, int y, int w, int h);
    void drawLine(int x1, int y1, int x2, int y2);
    void changeColor(int color);
};

#endif