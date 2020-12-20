#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include <string>
#include "MainMenu.h"

using namespace std;

/// <summary>
/// The game over view.
/// </summary>
class GameOverMenu : public Menu
{
protected:   

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="p"></param>
	/// <param name="g"></param>
	GameOverMenu(Player& p, GAME* g);
	 
	void onRetryClick(int id);

	void onQuitClick(int id);

	/// <summary>
	/// Event system with keyboard
	/// </summary>
	/// <param name="game"></param>
	virtual void onKeyDown(GAME* game);
};

#endif
