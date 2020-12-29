#ifndef ANIMATED_TEXTURE_H
#define ANIMATED_TEXTURE_H

#include "Texture.h"
#include <vector>

using namespace std;

/*
A class encapsulating an animated image.
*/
class AnimatedTexture : public Texture
{
protected:
	/// <summary>
	/// The textures under the hood
	/// </summary>
	vector<SDL_Texture*> frames;

 
public:
	/// <summary>
	/// Creates a new texture
	/// </summary>
	/// <param name="context"></param>
	/// <param name="id"></param>
	AnimatedTexture(RenderContext& context, string id);

	virtual ~AnimatedTexture();

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

 
};

#endif