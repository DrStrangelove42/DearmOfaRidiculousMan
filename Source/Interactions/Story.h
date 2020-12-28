#ifndef STORY_H
#define STORY_H

#include "../Base/game.h"

class Story
{
protected:
	void fromFile(string path);

public:
	Story();
	/// <summary>
	/// 
	/// </summary>
	/// <param name="time"></param>
	/// <param name=""></param>
	virtual void tick(int time, GAME* game);

	/// <summary>
	/// When a key is pushed on the keyboard.
	/// </summary>
	/// <param name="ea"></param>
	virtual void onKeyDown(GAME* game);
};

#endif