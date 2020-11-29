#include "Window.h"

Window::Window(string title, int w, int h) : w(w), h(h)
{
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		w, h, SDL_WINDOW_SHOWN);

	if (NULL == window)
	{
		throw runtime_error(SDL_GetError());
	}
}

Window::Window(string title, int w, int h, int x, int y) : w(w), h(h)
{
	window = SDL_CreateWindow(title.c_str(), x, y,
		w, h, SDL_WINDOW_SHOWN);

	if (NULL == window)
	{
		throw runtime_error(SDL_GetError());
	}
}

Window::~Window()
{
	if (NULL != window)
		SDL_DestroyWindow(window);
}

SDL_Renderer* Window::getRenderer()
{
	return  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

int Window::getX()
{
	int ret;
	SDL_GetWindowPosition(window, &ret, NULL);
	return ret;
}

int Window::getY()
{
	int ret;
	SDL_GetWindowPosition(window, NULL, &ret);
	return ret;
}

int Window::getW()
{
	return w;
}

int Window::getH()
{
	return h;
}

int Window::getId()
{
	SDL_GetWindowID(window);
}

