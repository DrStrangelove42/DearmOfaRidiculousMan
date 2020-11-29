#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>

using namespace std;

/*
A class encapsulating a rendering context.
*/
class Window
{
protected:
	/// <summary>
	/// The native window.
	/// </summary>
	SDL_Window* window;
	/// <summary>
	/// Size of the window
	/// </summary>
	int w, h;
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="title"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	Window(string title, int w, int h);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="title"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	Window(string title, int w, int h, int x, int y);
	~Window();

	/// <summary>
	/// Returns the appropriate renderer
	/// </summary>
	/// <returns></returns>
	SDL_Renderer* getRenderer();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int getX();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int getY();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int getW();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int getH();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int getId();

};

#endif