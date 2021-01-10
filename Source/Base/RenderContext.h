#ifndef RENDERCTXT_H
#define RENDERCTXT_H

#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "config.h"
#ifdef WIN6
#include <Windows.h>
#undef LoadString
#endif
#include <stdexcept>
#include <iostream>
#include <unordered_map>

using namespace std;

class Texture;

/// <summary>
/// RenderContext encapsulates a rendering context, that is used as an interface
/// with the graphics library to render the game.
/// </summary>
class RenderContext
{
protected:
	/// <summary>
	/// The native renderer.
	/// </summary>
	SDL_Renderer* renderer;

	/// <summary>
	/// The font used.
	/// </summary>
	static TTF_Font* FONT;
	
	/// <summary>
	/// The hashmap where <see cref="Texture">Textures</see> are stored.
	/// <see cref="Texture">Textures</see> beginning with 'text/' are reserved for text rendering.
	/// </summary>
	static unordered_map<string, Texture*> textures;
public:
	/// <summary>
	/// The size of the font used.
	/// </summary>
	static int FONTSIZE;
	
	/// <summary>
	/// Creates a new render context from the specified window.
	/// </summary>
	/// <param name="window"></param>
	RenderContext(Window& window);

	/// <summary>
	/// Render context destructor.
	/// </summary>
	virtual ~RenderContext();

	/// <summary>
	/// Erases the entire canvas.
	/// </summary>
	virtual void clear();

	/// <summary>
	/// Flushes the graphical modifications to appear on the screen.
	/// </summary>
	virtual void update();

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual SDL_Texture* fromSurface(SDL_Surface*);

	/// <summary>
	/// Does the actual rendering with low-level call to SDL.
	/// </summary>
	/// <param name="t">The SDL Texture structure</param>
	/// <param name="srcrect">The SDL rect structure to crop from the image (NULL to take everything).</param>
	/// <param name="dstrect">The SDL destination rectangle structure.</param>
	/// <param name="angle">Rotating angle, in degrees</param>
	/// <param name="center">Center of rotation.</param>
	/// <param name="flip">If the image is flipped.</param>
	virtual void doRender(SDL_Texture* t,
		const SDL_Rect* srcrect,
		const SDL_Rect* dstrect,
		const double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip);

	/// <summary>
	/// Draws a rectangle at the specified position, and with the specified dimensions, with the possibility to fill it or not.
	/// </summary>
	/// <param name="x">X coordinate</param>
	/// <param name="y">Y coordinate</param>
	/// <param name="w">Width</param>
	/// <param name="h">Height</param>
	/// <param name="fill">If the rectangle is filled with colour.</param>
	virtual void drawRectangle(int x, int y, int w, int h, bool fill = false);
	/// <summary>
	/// Draws a line from one point to another.
	/// </summary>
	/// <param name="x1">Start X coordinate</param>
	/// <param name="y1">Start Y coordinate</param>
	/// <param name="x2">End X coordinate</param>
	/// <param name="y2">End Y coordinate</param>
	virtual void drawLine(int x1, int y1, int x2, int y2);

	/// <summary>
	/// Sets the current colour, in the format 0xRRGGBBAA. 
	/// </summary>
	/// <param name="color">Colour code</param>
	virtual void changeColor(int color);


	/// <summary>
	/// Stops during ms milliseconds.
	/// </summary>
	/// <param name="ms">The delay</param>
	static void RenderSleep(unsigned int ms);

	/// <summary>
	/// Initialisation of the rendering module.
	/// </summary>
	/// <returns></returns>
	static bool RenderInit();

	/// <summary>
	/// Dump errors in the console.
	/// </summary>
	/// <returns></returns>
	static string RenderErrorDetails();

	/// <summary>
	/// Exits rendering module.
	/// </summary>
	static void RenderQuit();

	/// <summary>
	/// Use this function to load a Texture from a BMP file. If it succeeds,
	/// the Texture is saved in <textures> and will be loaded from memory next
	/// time this function is called for the same Texture ID.
	/// To load an AnimatedTexture (from files id0, ..., idN), prefix id with '*'.
	/// </summary>
	virtual Texture* LoadTexture(string id);

	/// <summary>
	/// Builds a Texture with the text inside.
	/// </summary>
	/// <param name="text"></param> 
	/// <param name="color"></param>
	/// <returns></returns>
	virtual Texture* LoadString(string text, int color = 0xffffffff);

	/// <summary>
	/// Loads a temporary Texture used to draw ever-changing text on screen.
	/// This way, we do not fill the RAM with every string possible.
	/// </summary>
	/// <param name="text"></param> 
	/// <param name="color"></param>
	/// <returns></returns>
	virtual Texture* LoadVolatileString(string text, int color);

	/// <summary>
	/// Loads a multiline text designed to fit in the specified width (in pixels).
	/// </summary>
	virtual Texture* LoadText(string text, int color, int width);

	/// <summary>
	/// Loads a multiline text designed to fit in the specified width (in pixels).
	/// </summary>
	/// <param name="text"></param>
	/// <param name="color"></param>
	/// <param name="backColor"></param>
	/// <param name="width"></param>
	/// <returns></returns>
	virtual Texture* LoadText(string text, int color, int backColor, int width, int padding = 0);

	/// <summary>
	/// Frees memory.
	/// </summary>
	static void FreeTextures();
};

#endif
