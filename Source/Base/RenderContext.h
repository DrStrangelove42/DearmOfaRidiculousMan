#include <SDL2/SDL.h>

/*
A class encapsulating a rendering context.
*/
class RenderContext
{
private:
    SDL_Renderer* renderer;
public:
    RenderContext();
    ~RenderContext();
 
    RenderContext::doRender(SDL_Texture* t,
        SDL_Texture* texture,
        const SDL_Rect* srcrect,
        const SDL_Rect* dstrect,
        const double           angle,
        const SDL_Point* center,
        const SDL_RendererFlip flip);


};
