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

/// <summary>
/// A Story is a type of gameplay in which the Player may talk with <see cref="NPC">NPCs</see> and answer multiple choice questions, thus what happens in the game depends on these choices. A Story is composed of <see cref="Part">Parts</see>, which are themselves composed of <see cref="Step">Steps</see>.
/// </summary>
class Story
{
protected:
	class Step;

	/// <summary>
	/// A Step is the main subdivision of a Part of a Story, and corresponds to one particular <see cref="Step::action">action</see> to be performed.
	/// </summary>
	class Step
	{
	public:
		/// <summary>
		/// Indicates whether or not the Step is done.
		/// </summary>
		bool done;
		/// <summary>
		/// Indicates whether or not the Step must block the Story, once it's done (and wait for a call to <see cref="Story::continueStory()>continueStory()</see>).
		/// </summary>
		bool wait;
		
		/// <summary>
		/// Action performed when the Part containing this Step is launched.
		/// </summary>
		function<void(GAME*)> action;
	
		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="action"></param>
		Step(function<void(GAME*)> action, bool wait=false);
	};

	/// <summary>
	/// A Part is the main subdivision of a Story, and is composed of <see cref="Step">Steps</see>. A Part is executed from start to finish, and may lead to a choice of several different <see cref="Part">Parts</see> (through choices offered by <see cref="NPC">NPCs</see>). If a branch occurs, the Part does not go forward automatically.
	/// </summary>
	class Part
	{
	public:
		/// <summary>
		/// The different <see cref="Step">Steps</see> that compose the Part.
		/// </summary>
		vector<Step*> scenario;

		/// <summary>
		/// Index of the current Step in this Part.
		/// </summary>
		int curStep;

		/// <summary>
		/// Indicates whether or not this Part is finished.
		/// </summary>
		bool done;

		/// <summary>
		/// Constructor.
		/// </summary>
		Part();

		/// <summary>
		/// Changes the Story to the ith Part.
		/// </summary>
		void branch(int i);

		/// <summary>
		/// Advances the Part to the next Step, or concludes the Part if there are none left.
		/// </summary>
		void nextStep();
	 
	};
	
	/// <summary>
	/// The different <see cref="Part">Parts</see> that compose the Story, which can be accessed thanks to the strings that refer to them upon creation.
	/// </summary>
	map<string, Part*> parts;

	/// <summary>
	/// The Part of the Story that is currently active.
	/// </summary>
	Part* curPart;
	
	/// <summary>
	/// Turns a file representing a Story (according to the encoding described in HowItWorks.txt) into a Story.
	/// </summary>
	/// <param name="path"></param>
	void fromFile(string path, GAME* game);

	/// <summary>
	/// Indicates whether or not we need to wait before continuing the story.
	/// </summary>
	bool waiting;
public:
	/// <summary>
	/// Constructor which uses the file found in path to create the Story.
	/// </summary>
	/// <param name="path"></param>
	Story(string path, GAME* game);

	/// <summary>
	/// Destructor.
	/// </summary>
	~Story();

	/// <summary>
	/// Time management.
	/// </summary>
	/// <param name="time"></param>
	/// <param name=""></param>
	virtual void tick(int time, GAME* game);

	/// <summary>
	/// Event system when a <see cref="GAME::key">key</see> is pressed on the keyboard.
	/// </summary>
	/// <param name="ea"></param>
	virtual void onKeyDown(GAME* game);

	/// <summary>
	/// Move to a new Step in the decision tree.
	/// </summary>
	/// <param name="index"></param>
	virtual void branch(int index);

	/// <summary>
	/// Move to a different Part.
	/// </summary>
	/// <param name="index"></param>
	virtual void changePart(string index);

	/// <summary>
	/// Makes the story advance if it was waiting for a certain action to finish.
	/// </summary>
	void continueStory();

	/// <summary>
	/// Returns the <see cref="Part::curStep">current Step</see> of the Story.
	/// </summary>
	Step* getCurrentStep();
};

#endif
