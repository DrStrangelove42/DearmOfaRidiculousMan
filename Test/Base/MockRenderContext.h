#ifndef MOCKRENDERCTXT_H
#define MOCKRENDERCTXT_H

#include "../../Source/Base/RenderContext.h"

using namespace std;

class Texture;

/// <summary>
/// A class encapsulating a rendering context, that is an object used as an interface
/// with the graphics library to render the game.
/// </summary>
class MockRenderContext : public RenderContext
{

public:

	/// <summary>
	/// Erases the entire canevas.
	/// </summary>
	void clear();

	/// <summary>
	/// Flushes the graphical modifications to appear on the screen.
	/// </summary>
	void update();

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	SDL_Texture* fromSurface(SDL_Surface*);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t"></param>
	/// <param name="srcrect"></param>
	/// <param name="dstrect"></param>
	/// <param name="angle"></param>
	/// <param name="center"></param>
	/// <param name="flip"></param>
	void doRender(SDL_Texture* t,
		const SDL_Rect* srcrect,
		const SDL_Rect* dstrect,
		const double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="fill"></param>
	void drawRectangle(int x, int y, int w, int h, bool fill = false);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	void drawLine(int x1, int y1, int x2, int y2);

	/// <summary>
	/// Sets the current color, in the format 0xRRGGBBAA 
	/// </summary>
	/// <param name="color"></param>
	void changeColor(int color);

	/// <summary>
/// Stops during ms milliseconds.
/// </summary>
/// <param name="ms">The delay</param>
	virtual void RenderSleep(unsigned int ms) ;
	 
	/// <summary>
	/// Use this function to load a texture from a BMP file. If it succeeds,
	/// the texture is saved in <textures> and will be loaded from memory next
	/// time this function is called for the same texture ID.
	/// To load an animated texture (from files id0, ..., idN), prefix id with '*'.
	/// </summary>
	Texture* LoadTexture(string id);

	/// <summary>
	/// Builds a texture with the text inside.
	/// </summary>
	/// <param name="text"></param> 
	/// <param name="color"></param>
	/// <returns></returns>
	Texture* LoadString(string text, int color = 0xffffffff, int backcolor = 0);

	/// <summary>
	/// Loads a temporary texture used to draw ever-changing text on screen.
	/// This way, we do not fill the RAM with every string possible.
	/// </summary>
	/// <param name="text"></param> 
	/// <param name="color"></param>
	/// <returns></returns>
	virtual Texture* LoadVolatileString(string text, int color, int backColor = 0) ;

	/// <summary>
	/// Loads a multiline text designed to fit in the specified width (in pixels).
	/// </summary>
	Texture* LoadText(string text, int color, int width);

	/// <summary>
	/// Loads a multiline text designed to fit in the specified width (in pixels).
	/// </summary>
	/// <param name="text"></param>
	/// <param name="color"></param>
	/// <param name="backColor"></param>
	/// <param name="width"></param>
	/// <returns></returns>
	Texture* LoadText(string text, int color, int backColor, int width, int padding = 0);

	/// <summary>
	/// Loads a single line of text
	/// </summary>
	/// <param name="text">The text to be displayed.</param>
	/// <param name="colors">The list of colours defining the animation.</param>
	/// <param name="interval">Time delay, in ms, between each colour.</param>
	/// <param name="loop">Tells whether the animations keeps on going after the last color.</param>
	/// <returns></returns>
	virtual Texture* LoadAnimatedString(string text, list<int> colors, int interval, bool loop = true) ;

	/// <summary>
	/// Loads a single line of text with an animation on the background.
	/// </summary>
	/// <param name="text">The text to be displayed.</param>
	/// <param name="colors">The list of colours defining the animation.</param>
	/// <param name="bgcolors">The list of background colours of the animation. It must have the same size as the colors list.</param>
	/// <param name="interval">Time delay, in ms, between each colour.</param>
	/// <param name="loop">Tells whether the animations keeps on going after the last color.</param>
	/// <returns></returns>
	virtual Texture* LoadAnimatedBoxedString(string text, list<int> colors, list<int> bgcolors, int interval, bool loop = true)  ;

	/// <summary>
		/// Loads a string with an icon on the left.
		/// </summary>
		/// <param name="text"></param>
		/// <param name="textureId"></param>
		/// <param name="color"></param>
		/// <param name="backColor"></param>
		/// <returns></returns>
	virtual Texture* LoadStringWithIcon(string text, string textureId, int color, int padding = 5, int backColor = 0)  ;

};

#endif