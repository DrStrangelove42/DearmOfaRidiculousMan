#include "MockRenderContext.h"

MockRenderContext::MockRenderContext(Window& w) :RenderContext(w)
{
}

void MockRenderContext::clear()
{
}

void MockRenderContext::update()
{
}

SDL_Texture* MockRenderContext::fromSurface(SDL_Surface*)
{
	return nullptr;
}

void MockRenderContext::doRender(SDL_Texture* t, const SDL_Rect* srcrect, const SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip)
{
}

void MockRenderContext::drawRectangle(int x, int y, int w, int h, bool fill)
{
}

void MockRenderContext::drawLine(int x1, int y1, int x2, int y2)
{
}

void MockRenderContext::changeColor(int color)
{
}

Texture* MockRenderContext::LoadTexture(string id)
{
	cout << "LOAD TEXTETER" << endl;
	return nullptr;
}

Texture* MockRenderContext::LoadString(string text, int color)
{
	return nullptr;
}

Texture* MockRenderContext::LoadVolatileString(string text, int color)
{
	return nullptr;
}

Texture* MockRenderContext::LoadText(string text, int color, int width)
{
	return nullptr;
}

Texture* MockRenderContext::LoadText(string text, int color, int backColor, int width, int padding)
{
	return nullptr;
}
