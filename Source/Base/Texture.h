#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include "RenderContext.h"
#include <string>
#include "config.h"
#include <stdexcept>

using namespace std;

//In order to access easily to the protected members of a Texture via its derivated class.
class AnimatedTexture;

/// <summary>
/// A Texture is what gives the appearance to anything present in the Window.
/// </summary>
class Texture
{
friend class AnimatedTexture; //see above.
protected:
	/// <summary>
	/// The texture under the hood, courtesy of the SDL library.
	/// </summary>
	SDL_Texture* texture;

	/// <summary>
	/// Width of the AnimatedTexture.
	/// </summary>
	int w;
	
	/// <summary>
	/// Height of the AnimatedTexture.
	/// </summary>
	int h;
	
	/// <summary>
	/// Low level helper function to open bitmap files, we ignore the errors when we are looking for the last <see cref="AnimatedTexture::frames>frame</see> of an AnimatedTexture.
	/// </summary>
	/// <param name="context"></param>
	/// <param name="id"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="ignoreErrors"></param>
	/// <returns></returns>
	SDL_Texture* internalLoadTexture(RenderContext& context, string id, int& w, int& h, bool ignoreErrors = false);

	/// <summary>
	/// To avoid code duplication, this subfunction is called from render in the base class Texture but can
	/// also be called from derived classes.
	/// </summary>
	/// <param name=""></param>
	/// <param name="context"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="angle"></param>
	/// <param name="center"></param>
	/// <param name="flip"></param>
	void internalRender(SDL_Texture* tx, RenderContext& context, int x, int y, int width, int height, double angle, SDL_Point* center, SDL_RendererFlip flip)
	{
		if (NULL != tx)
		{
			SDL_Rect dst = { x + VIEW_OFFSET_X, y + VIEW_OFFSET_Y, width, height };

			context.doRender(tx, NULL, &dst, angle, center, flip);
		}
	}

	/// <summary>
	/// To avoid code duplication, this subfunction is called from render in the base class Texture but can
	/// also be called from derived classes. Also, it doesn't change the size of the Texture.
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="context"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="angle"></param>
	/// <param name="center"></param>
	/// <param name="flip"></param>
	void internalRenderUnscaled(SDL_Texture* tx, RenderContext& context, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip)
	{
		if (NULL != tx)
		{
			SDL_Rect dst = { x + VIEW_OFFSET_X, y + VIEW_OFFSET_Y, w, h };

			/*Later : to clip an image*/
			/*if (clip != NULL) <- <SDL_Rect* clip> an argument of our function
			{
				renderQuad.w = clip->w;
				renderQuad.h = clip->h;
			}*/

			context.doRender(tx, NULL, &dst, angle, center, flip);
		}
	}

public:
	/// <summary>
	/// Encapsulates an existing native Texture.
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	Texture(SDL_Texture* texture, int w, int h);

	/// <summary>
	/// Creates a new Texture.
	/// </summary>
	/// <param name="context"></param>
	/// <param name="id"></param>
	Texture(RenderContext& context, string id);

	/// <summary>
	/// Bit of code used to load a bitmap file. Used in Texture as well as in other
	/// parts of the program, which is why factorization is necessary here.
	/// </summary>
	/// <param name="id"></param>
	/// <param name="ignoreErrors"></param>
	/// <returns></returns>
	static inline SDL_Surface* internalLoadBitmapSurface(string id, bool ignoreErrors)
	{
		SDL_Surface* bmp = NULL;

		bmp = SDL_LoadBMP(("Res/" + id + ".bmp").c_str());

		if (NULL == bmp)
		{
			if (!ignoreErrors)
				cout << "Unable to load texture #" + id + " : " + string(SDL_GetError()) << endl;
			return NULL;
		}

		SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xff, 0, 0xff));
		return bmp;
	}

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~Texture();

	/*
	For if we wish to use colours to modify textures (for example so that corresponding keys and doors are the same colour)
	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	
	//Set blending
	void setBlendMode(SDL_BlendMode blending);
	
	//Set alpha modulation
	void setAlpha(Uint8 alpha);
	*/

	/// <summary>
	/// Renders Texture at any given point, without scaling.
	/// </summary>
	/// <param name="context"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="angle"></param>
	/// <param name="center"></param>
	/// <param name="flip"></param>
	virtual void renderUnscaled(RenderContext& context, int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/// <summary>
	/// Renders Texture at any given point.
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
	/// Gets the <see cref="Texture::w">width</see> of this Texture.
	/// </summary>
	/// <returns></returns>
	int getWidth();

	/// <summary>
	/// Gets the <see cref="Texture::h">height</see> of this Texture.
	/// </summary>
	/// <returns></returns>
	int getHeight();
};

#endif
