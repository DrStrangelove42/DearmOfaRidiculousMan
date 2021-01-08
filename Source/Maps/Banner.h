#ifndef BANNER_H
#define BANNER_H

#include <string>
#include "Menu.h"
#include "../Base/config.h"

using namespace std;

/// <summary>
/// The Menu class is an abstract class representing a generic menu view, with buttons and text.
/// </summary>
class Banner : public Menu
{ 
protected:
	int delay;
	int beginTime;
	string worldName;
	int mapIndex;
	int roomIndex;
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="p"></param>
	/// <param name="g"></param>
	Banner(Player& p, GAME* g, const  string text, const  int delay, const string worldName, const  int mapIndex, const  int roomIndex);

	void reset();

	virtual ~Banner();
	
	/// <summary>
	/// Event system from the keyboard
	/// </summary>
	/// <param name="game"></param>
	virtual void onKeyDown(GAME* game);
 
	/// <summary>
	/// Time management 
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	virtual void tick(int time, GAME* game);
 
};

#endif
