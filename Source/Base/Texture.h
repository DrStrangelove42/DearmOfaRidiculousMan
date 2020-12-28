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
protected:
	/// <summary>
	/// The texture under the hood
	/// </summary>
	SDL_Texture* texture;

	/// <summary>
	/// Witdh
	/// </summary>
	int w;
	/// <summary>
	/// Height
	/// </summary>
	int h;
	/// <summary>
	/// Low level helper function to open bitmap files.
	/// </summary>
	/// <param name="context"></param>
	/// <param name="id"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <returns></returns>
	SDL_Texture* internalLoadTexture(RenderContext& context, string id, int& w, int& h);
public:
	/// <summary>
	/// Encapsulates an existing native texture
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	Texture(SDL_Texture* texture, int w, int h);

	/// <summary>
	/// Creates a new texture
	/// </summary>
	/// <param name="context"></param>
	/// <param name="id"></param>
	Texture(RenderContext& context, string id);

	
	virtual ~Texture();

	/*//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);*/

	/// <summary>
	/// Renders texture at given point, without scaling
	/// </summary>
	/// <param name="context"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="angle"></param>
	/// <param name="center"></param>
	/// <param name="flip"></param>
	virtual void renderUnscaled(RenderContext& context, int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/// <summary>
	/// Renders texture at given point
	/// </summary>
	/// <param name="context"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="angle"></param>
	/// <param name="center"></param>
	/// <param name="flip"></param>
	virtual void render(RenderContext& context, int x, int y, int width, int height, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/// <summary>
	/// Gets the width of this Texture.
	/// </summary>
	/// <returns></returns>
	int getWidth();

	/// <summary>
	/// Gets the height of this Texture.
	/// </summary>
	/// <returns></returns>
	int getHeight();
};

#endif