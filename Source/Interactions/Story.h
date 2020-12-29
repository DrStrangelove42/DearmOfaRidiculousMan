#ifndef STORY_H
#define STORY_H

#include <string>
#include "../Base/game.h"
#include "../Base/config.h"
#include "../Base/utils.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Story
{
	class Part
	{

	};

protected:
	/// <summary>
	/// The different parts of the story to play.
	/// </summary>
	vector<Part*> parts;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="path"></param>
	void fromFile(string path);

	string getLineType(string& line);
public:
	/// <summary>
	/// Name of the story to load from data files.
	/// </summary>
	/// <param name="path"></param>
	Story(string path);

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