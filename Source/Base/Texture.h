#include <SDL2/SDL.h>

using namespace std;

/*
A class encapsulating a texture that can be rendered.
*/
class Texture
{
private:
    /* The texture under the hood */
    SDL_Texture* texture;

    /* Dimensions */
    int w;
    int h;
public:
    Texture(RenderContext& context, string id);
    ~Texture();

    //Set color modulation
    void setColor(Uint8 red, Uint8 green, Uint8 blue);

    //Set blending
    void setBlendMode(SDL_BlendMode blending);

    //Set alpha modulation
    void setAlpha(Uint8 alpha);

    //Renders texture at given point
    void render(int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Gets image dimensions
    int getWidth();
    int getHeight();


};
