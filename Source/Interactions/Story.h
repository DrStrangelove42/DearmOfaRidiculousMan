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
		bool done;
		/// <summary>
		/// If the step must block the story, once it's done (wait for a call to <code>continueStory()</code>)
		/// </summary>
		bool wait;
		/// <summary>
		/// The action function takes the main game as a parameter.
		/// </summary>
		function<void(GAME*)> action;
	
		/// <summary>
		/// Creates a new step in the story.
		/// </summary>
		/// <param name="action">Action performed when the part containing this step is launched.</param>
		Step(function<void(GAME*)> action, bool wait=false);


	};

	/// <summary>
	/// Main subdivision of the story.
	/// </summary>
	class Part
	{
	public:
		/// <summary>
		/// If a branch occurs, the part does not go forward automatically.
		/// </summary>
		vector<Step*> scenario;
		int curStep;
		bool done;

		Part();
		void branch(int i);

		void nextStep();
	 
	};
	
protected:
	/// <summary>
	/// The different parts of the story to play.
	/// </summary>
	map<string, Part*> parts;
	Part* curPart;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="path"></param>
	void fromFile(string path, GAME* game);

	bool waiting;
public:
	/// <summary>
	/// Name of the story to load from data files.
	/// </summary>
	/// <param name="path"></param>
	Story(string path, GAME* game);

	~Story();

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

	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	virtual void changePart(string index);

	/// <summary>
	/// 
	/// </summary>
	void continueStory();

	Step* getCurrentStep();
};

#endif