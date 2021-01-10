#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include <string>
#include "MainMenu.h"

using namespace std;

/// <summary>
/// The GameOverMenu is a type of Menu used when the Player is killed.
/// </summary>
class GameOverMenu : public Menu
{
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="p"></param>
	/// <param name="g"></param>
	GameOverMenu(Player& p, GAME* g);

	/// <summary>
	/// Performs the wanted action when the user clicks on the retry Button.
	/// </summary>
	/// <param name="id"></param>
	void onRetryClick(int id);

	/// <summary>
	/// Performs the wanted action when the user clicks on the quit Button.
	/// </summary>
	/// <param name="id"></param>
	void onQuitClick(int id);

	/// <summary>
	/// Event system when a <see cref="GAME::key">key</see> is pressed on the keyboard.
	/// </summary>
	/// <param name="game"></param>
	virtual void onKeyDown(GAME* game);
};

#endif
