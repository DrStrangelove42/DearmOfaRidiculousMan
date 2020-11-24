#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include "RenderContext.h"
#include <string>
#include "config.h"
#include <stdexcept>

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
	Texture(SDL_Texture* texture, int w, int h);
	~Texture();

	/*//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);*/

	//Renders texture at given point
	void renderUnscaled(RenderContext& context, int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void render(RenderContext& context, int x, int y, int width, int height, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();
};

#endif