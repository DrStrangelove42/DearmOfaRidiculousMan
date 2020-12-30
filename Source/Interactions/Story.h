#ifndef STORY_H
#define STORY_H

#include <string>
#include "../Base/game.h"
#include "../Base/config.h"
#include "../Base/utils.h"
#include <fstream>
#include <functional>
#include <iostream>
#include <vector> 

using namespace std;

class Story
{
	class Step;

	/// <summary>
	/// A point in a part of the story.
	/// </summary>
	class Step
	{
	public:
		/// <summary>
		/// The different branches of the story from this point.
		/// </summary>
		vector<Step*> choices;
		/// <summary>
		/// The action function takes the main game as a parameter.
		/// </summary>
		function<void(GAME*)> action;
	
	};

	/// <summary>
	/// Main subdivision of the story.
	/// </summary>
	class Part
	{
	protected:
		Step decisionTree;
		Step* curStep;

	public:
		void branch(int i);
	};
	
protected:
	/// <summary>
	/// The different parts of the story to play.
	/// </summary>
	vector<Part*> parts;
	int curPart;
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

	/// <summary>
	/// Move to a new step in the decision tree.
	/// </summary>
	/// <param name="index"></param>
	virtual void branch(int index);

	virtual void changePart(int index);
};

#endif