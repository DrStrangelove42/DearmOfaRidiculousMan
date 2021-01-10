#ifndef MENU_H
#define MENU_H

#include <string>
#include "../Base/game.h"
#include "../Base/Entity.h"
#include "../Base/config.h"
#include "../Base/utils.h"
#include "../Characters/Player.h"
#include "../Interactions/Button.h"
#include <iostream>
#include <fstream>
#include "../Objects/Object.h"
#include "../Objects/Chest.h"
#include "../Objects/Door.h"
#include "../Objects/Key.h"
#include "../Objects/Warp.h"
#include "../Maps/Map.h"
 
using namespace std;

/// <summary>
/// The Menu class is an abstract class representing a generic menu view, with <see cref="Button">Buttons</see> and text.
/// </summary>
class Menu : public Map
{
protected:
	/// <summary>
	/// The <see cref="Button">Buttons</see> in the Menu that the user can click on.
	/// </summary>
	list<Button*> buttons;
	/// <summary>
	/// The <see cref="Label">Labels</see> in the Menu that display text.
	/// </summary>
	list<Label*> labels;
 
	/// <summary>
	/// The current GAME.
	/// </summary>
	GAME* game;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="p"></param>
	/// <param name="g"></param>
	Menu(Player& p, GAME* g);

	/// <summary>
	/// Destructor.
	/// </summary>	
	virtual ~Menu();
	
	/// <summary>
	/// Event system when a <see cref="GAME::key">key</see> is pressed on the keyboard.
	/// </summary>
	/// <param name="game"></param>
	virtual void onKeyDown(GAME* game) = 0;
	
	/// <summary>
	/// <see cref="RenderContext">Rendering</see> method, enabling the <see cref="RenderContext::renderer">renderer</see> to take the offset (in <see cref="Block">Blocks</see>) into account.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)const;
	
	/// <summary>
	/// Time management. 
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	virtual void tick(int time, GAME* game);
	
	/// <summary>
	/// Adds a Button to the Menu.
	/// </summary>
	/// <param name="b"></param>
	void addButton(Button* b);
	
	/// <summary>
	/// Adds a Label to the menu.
	/// </summary>
	/// <param name="l"></param>
	void addLabel(Label* l);
};

#endif
