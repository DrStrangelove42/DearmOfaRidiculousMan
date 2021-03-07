#include "InfoTipButton.h"

InfoTipButton::InfoTipButton(Texture* texture, RenderContext& renderer, int x, int y, int id, function<void(int)> onClick, string infoTip, int infoTipColor) :
	Button(texture, x, y, id, onClick)
{
	setInfoTip(infoTip, renderer, infoTipColor); //max width  = info window width.
}

InfoTipButton::InfoTipButton(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, string infoTip, int infoTipColor, int color) :
	Button(caption, r, x, y, id, onClick, color)
{
	setInfoTip(infoTip, r, infoTipColor); //max width  = info window width.
}



InfoTipButton::InfoTipButton(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color, int OverColor, string infoTip, int infoTipColor) :
	Button(caption, r, x, y, id, onClick, color, overClr)
{
	setInfoTip(infoTip, r, infoTipColor); //max width  = info window width.
}

void InfoTipButton::setInfoTip(string infoTip, RenderContext& r, int color)
{
	infoTipTx = r.LoadText(infoTip, color, 0x000000AA, SZ_INFOSWIDTH, 5); //max width  = info window width.
}

void InfoTipButton::render(RenderContext& renderer, int offsetX, int offsetY) const
{
	if (mouseOver)
	{
		renderer.changeColor(overClr);
		renderer.drawRectangle(x - outerMargin, y - outerMargin, loadedTx->getWidth() + 2 * outerMargin, loadedTx->getHeight() + 2 * outerMargin);
	}

	Label::render(renderer, offsetX, offsetY);
}

void InfoTipButton::tick(int time, GAME* game)
{
	if (mouseOver)
	{
		game->currentMap->registerTopMostTexture("ShopBtnInfoTip", infoTipTx, { SZ_SCREENWIDTH - infoTipTx->getWidth() - SZ_INFOSWIDTH, y });
	}
}
