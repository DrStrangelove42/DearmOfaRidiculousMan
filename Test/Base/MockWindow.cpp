#include "MockWindow.h"

MockWindow::MockWindow()
{
}

SDL_Renderer* MockWindow::getRenderer()
{
	return (SDL_Renderer*)(0xC07FEFE);
}


