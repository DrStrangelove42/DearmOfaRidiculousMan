#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>

using namespace std;

/// <summary>
/// A Window encapsulates a RenderContext.
/// </summary>
class Window
{
protected:
	/// <summary>
	/// The native Window.
	/// </summary>
	SDL_Window* window;
	
	/// <summary>
	/// Size of the Window.
	/// </summary>
	int w, h;
public:
	/// <summary>
	/// Dummy constructor (this should ideally be replaced by a generic Window class without any reference to a graphic library).
	/// </summary>
	Window();

	/// <summary>
	/// Constructor using the dimensions of the window, placed in the centre.
	/// </summary>
	/// <param name="title"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	Window(string title, int w, int h);

	/// <summary>
	/// Constructor using the dimensions of the window and the position.
	/// </summary>
	/// <param name="title"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	Window(string title, int w, int h, int x, int y);

	/// <summary>
	/// Destructor.
	/// </summary>
	~Window();

	/// <summary>
	/// Returns the appropriate <see cref="RendererContext::renderer">renderer</see>.
	/// </summary>
	/// <returns></returns>
	virtual SDL_Renderer* getRenderer();

	/// <summary>
	/// Returns the x coordinate of the Window.
	/// </summary>
	/// <returns></returns>
	virtual int getX();

	/// <summary>
	/// Returns the y coordinate of the Window.
	/// </summary>
	/// <returns></returns>
	virtual int getY();

	/// <summary>
	/// Returns the <see cref="Window::w">width</see> of the Window.
	/// </summary>
	/// <returns></returns>
	virtual int getW();

	/// <summary>
	/// Returns the <see cref="Window::h">height</see> of the Window.
	/// </summary>
	/// <returns></returns>
	virtual int getH();

	/// <summary>
	/// Returns the identifier of the Window.
	/// </summary>
	/// <returns></returns>
	virtual int getId();

};

#endif
