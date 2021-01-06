#ifndef RENDERCTXTBASE_H
#define RENDERCTXTBASE_H

#include <string>

using namespace std;

class Texture;

/// <summary>
/// A class encapsulating a rendering context, that is an object used as an interface
/// with the graphics library to render the game.
/// </summary>
class RenderContextBase
{

public:

	virtual ~RenderContextBase() {}

	/// <summary>
	/// Erases the entire canevas.
	/// </summary>
	virtual void clear() = 0;

	/// <summary>
	/// Flushes the graphical modifications to appear on the screen.
	/// </summary>
	virtual void update() = 0;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="fill"></param>
	virtual void drawRectangle(int x, int y, int w, int h, bool fill = false) = 0;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	virtual void drawLine(int x1, int y1, int x2, int y2) = 0;

	/// <summary>
	/// Sets the current color, in the format 0xRRGGBBAA 
	/// </summary>
	/// <param name="color"></param>
	virtual void changeColor(int color) = 0;


	/// <summary>
	/// Stops during ms milliseconds.
	/// </summary>
	/// <param name="ms">The delay</param>
	static void RenderSleep(unsigned int ms) ;

	/// <summary>
	/// Initialisation of the rendering module
	/// </summary>
	/// <returns></returns>
	static bool RenderInit() ;

	/// <summary>
	/// Dump errors in the console.
	/// </summary>
	/// <returns></returns>
	static string RenderErrorDetails() ;

	/// <summary>
	/// Exits rendering module
	/// </summary>
	static void RenderQuit() ;

	/// <summary>
	/// Use this function to load a texture from a BMP file. If it succeeds,
	/// the texture is saved in <textures> and will be loaded from memory next
	/// time this function is called for the same texture ID.
	/// To load an animated texture (from files id0, ..., idN), prefix id with '*'.
	/// </summary>
	virtual Texture* LoadTexture(string id) = 0;

	/// <summary>
	/// Builds a texture with the text inside.
	/// </summary>
	/// <param name="text"></param> 
	/// <param name="color"></param>
	/// <returns></returns>
	virtual Texture* LoadString(string text, int color = 0xffffffff) = 0;

	/// <summary>
	/// Loads a temporary texture used to draw ever-changing text on screen.
	/// This way, we do not fill the RAM with every string possible.
	/// </summary>
	/// <param name="text"></param> 
	/// <param name="color"></param>
	/// <returns></returns>
	virtual Texture* LoadVolatileString(string text, int color) = 0;

	/// <summary>
	/// Loads a multiline text designed to fit in the specified width (in pixels).
	/// </summary>
	virtual Texture* LoadText(string text, int color, int width) = 0;

	/// <summary>
	/// Loads a multiline text designed to fit in the specified width (in pixels).
	/// </summary>
	/// <param name="text"></param>
	/// <param name="color"></param>
	/// <param name="backColor"></param>
	/// <param name="width"></param>
	/// <returns></returns>
	virtual Texture* LoadText(string text, int color, int backColor, int width, int padding = 0) = 0;
};

#endif