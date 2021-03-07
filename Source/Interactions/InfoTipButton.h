#ifndef INFOTIPBUTTON_H
#define INFOTIPBUTTON_H

#include <string>
 
#include "Button.h"
#include "../Maps/Map.h"

using namespace std;

/// <summary>
/// A InfoTipButton is a Label that can be clicked on by the user to perform a certain action.
/// </summary>
class InfoTipButton : public Button
{
protected:
	/// <summary>
	/// The info to be displayed when the user hovers the button with the mouse cursor.
	/// </summary>
	Texture* infoTipTx;
public:
	/// <summary>
	/// Creates a new button.
	/// </summary>
	/// <param name="texture">A pointer to an already created texture</param>
	/// <param name="x">X coordinate (screen coordinates)</param>
	/// <param name="y">Y coordinate (screen coordinates)</param>
	/// <param name="id">Identifier that is the parameter of the callback function.</param>
	/// <param name="onClick">Callback function called when the user clicks on the button.</param>
	InfoTipButton(Texture* texture, RenderContext& renderer, int x, int y, int id, function<void(int)> onClick, string infoTip, int infoTipColor=0xffffffff);
	/// <summary>
	/// Creates a new button.
	/// </summary>
	/// <param name="caption">Text of the button</param>
	/// <param name="r">The render context used to create the underlying texture.</param>
	/// <param name="x">X coordinate (screen coordinates)</param>
	/// <param name="y">Y coordinate (screen coordinates)</param>
	/// <param name="id">Identifier that is the parameter of the callback function.</param>
	/// <param name="onClick">Callback function called when the user clicks on the button.</param>
	/// <param name="color">Text color, white by default</param>
	InfoTipButton(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, string infoTip, int infoTipColor = 0xffffffff, int color = 0xffffffff);
	/// <summary>
	/// Creates a new button.
	/// </summary>
	/// <param name="caption">Text of the button</param>
	/// <param name="r">The render context used to create the underlying texture.</param>
	/// <param name="x">X coordinate (screen coordinates)</param>
	/// <param name="y">Y coordinate (screen coordinates)</param>
	/// <param name="id">Identifier that is the parameter of the callback function.</param>
	/// <param name="onClick">Callback function called when the user clicks on the button.</param>
	/// <param name="color">Text color.</param>
	/// <param name="OverColor">Text color in active mode.</param>
	InfoTipButton(string caption, RenderContext& r, int x, int y, int id, function<void(int)> onClick, int color, int OverColor, string infoTip, int infoTipColor = 0xffffffff);
 
	/// <summary>
	/// Sets the info text.
	/// </summary>
	/// <param name="infoTip"></param>
	/// <param name="color"></param>
	void setInfoTip(string infoTip, RenderContext& r, int color);

	/// <summary>
	/// For buttons, the rendering is in absolute position (no offset).
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX">Ignored.</param>
	/// <param name="offsetY">Ignored.</param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)const;
 
	/// <summary>
	/// Time management : registration of infotip.
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	virtual void tick(int time, GAME* game);
};

#endif
