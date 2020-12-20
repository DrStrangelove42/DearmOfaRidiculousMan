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
/// The Menu class is an abstract class representing a generic menu view, with buttons and text.
/// </summary>
class Menu : public Map
{
protected:
	/// <summary>
	/// 
	/// </summary>
	list<Button*> buttons;
	/// <summary>
	/// 
	/// </summary>
	list<Label*> labels;
 
	/// <summary>
	/// 
	/// </summary>
	GAME* game;

	/// <summary>
	/// Allows to exit a loop when 
	/// </summary>
	bool deleting;

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="p"></param>
	/// <param name="g"></param>
    Menu(Player& p, GAME* g);

	virtual ~Menu();
	/// <summary>
	/// Events from the mouse
	/// </summary>
	/// <param name="md"></param>
	virtual void onMouseEvent(MOUSE_DATA* md);
	/// <summary>
	/// Event system from the keyboard
	/// </summary>
	/// <param name="game"></param>
	virtual void onKeyDown(GAME* game) = 0;
	/// <summary>
	/// Rendering method, enabling the renderer to take the offset (in blocks) into account.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)const;
	
	/// <summary>
	/// Time management 
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	virtual void tick(int time, GAME* game);
	/// <summary>
	/// Adds a button in the menu view.
	/// </summary>
	/// <param name="b"></param>
	void addButton(Button* b);
	/// <summary>
	/// Adds a label in the menu.
	/// </summary>
	/// <param name="l"></param>
	void addLabel(Label* l);
};

#endif
