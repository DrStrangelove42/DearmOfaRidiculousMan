#ifndef ANIMATED_TEXTURE_H
#define ANIMATED_TEXTURE_H

#include "Texture.h"
#include <vector>
#include <list>
#include "config.h"
#include "utils.h"

using namespace std;

/// <summary>
/// An AnimatedTexture is a Texture that seems to be animated (by displaying several successive, slightly different <see cref="Texture">Textures</see>).
/// </summary>
class AnimatedTexture : public Texture
{
protected:
	/// <summary>
	/// The textures under the hood, courtesy of the SDL library.
	/// </summary>
	vector<SDL_Texture*> frames;

	/// <summary>
	/// The number of render times between each frame (depending on the actual FPS).
	/// </summary>
	int delay;

	/// <summary>
	/// The time at which the image displayed by the AnimatedTexture was last changed.
	/// </summary>
	int lastTime;

	/// <summary>
	/// The index of the frame in <see cref="AnimatedTexture::frames">frames</see>that is currently being displayed.
	/// </summary>
	int curFrame;

	/// <summary>
	/// The number of images in <see cref="AnimatedTexture::frames">frames</see>.
	/// </summary>
	int frameCount;

	/// <summary>
	/// Whether the textures goes back to its first frame at the end of the animation or not.
	/// </summary>
	bool loop;
public:
	/// <summary>
	/// Constructor of a new AnimatedTexture from files id0, ..., idN, where N is deduced from the available files.
	/// </summary>
	/// <param name="context"></param>
	/// <param name="id">Root of the names</param>
	/// <param name="delay">Delay, in ms, between two frames.</param>
	AnimatedTexture(RenderContext& context, string id, int delay = 500);

	/// <summary>
	/// Native constructor of an animated image with specified compound images and delay.
	/// </summary>
	/// <param name="content"></param>
	/// <param name="id"></param>
	/// <param name="delay"></param>
	AnimatedTexture(list<Texture*>& content, int delay = 500, bool loop = true);

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~AnimatedTexture();

	/// <summary>
	/// Renders the AnimatedTexture at any given point, without scaling.
	/// </summary>
	/// <param name="context"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="angle"></param>
	/// <param name="center"></param>
	/// <param name="flip"></param>
	virtual void renderUnscaled(RenderContext& context, int x, int y, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/// <summary>
	/// Renders the AnimatedTexture at any given point.
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
	/// Sets the <see cref="AnimatedTexture::delay">delay</see> of the AnimatedTexture.
	/// </summary>
	/// <param name="d"></param>
	void setDelay(int d);

	/// <summary>
	/// Resets the animation counter.
	/// </summary>
	void reset();
};

#endif
