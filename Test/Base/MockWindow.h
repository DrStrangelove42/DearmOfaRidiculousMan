#ifndef MOCKWINDOW_H
#define MOCKWINDOW_H

#include "../../Source/Base/Window.h"
#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>

using namespace std;

/*
A mock class for the Window, without any capacity for rendering.
*/
class MockWindow : public Window
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="title"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	MockWindow();

	/// <summary>
	/// Do not do anything with this dummy renderer.
	/// </summary>
	/// <returns></returns>
	SDL_Renderer* getRenderer();
};

#endif