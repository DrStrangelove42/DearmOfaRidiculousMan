#include "MockRenderContext.h"
 

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

void MockRenderContext::RenderSleep(unsigned int ms)
{
}

Texture* MockRenderContext::LoadTexture(string id)
{
	return nullptr;
}

Texture* MockRenderContext::LoadString(string text, int color)
{
	return nullptr;
}

Texture* MockRenderContext::LoadVolatileString(string text, int color,int b)
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

Texture* MockRenderContext::LoadAnimatedString(string text, list<int> colors, int interval, bool loop)
{
	return nullptr;
}

Texture* MockRenderContext::LoadAnimatedBoxedString(string text, list<int> colors, list<int> bgcolors, int interval, bool loop)
{
	return nullptr;
}

Texture* MockRenderContext::LoadStringWithIcon(string text, string textureId, int color, int padding, int backColor)
{
	return nullptr;
}
