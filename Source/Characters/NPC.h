#ifndef NPC_H
#define NPC_H

#include "../Objects/Object.h"
#include <functional>
#include "../Interactions/Button.h"
#include <list>

class NPC : Object
{
protected:
	string speech;

	Texture* text;

	/// <summary>
	/// 
	/// </summary>
	list<Button*> choices;
public:
	NPC(string identifier, string speech, int posx, int posy, string tx, RenderContext& renderer, bool trav);

	/// <summary>
	/// The following function describes how each type of object interacts with the player.
	/// Returns true if the object has been picked up (thus informing that we should remove it from the room)
	/// </summary>
	/// <param name="game"></param>
	virtual bool updateObject(GAME* game);
	void addChoice(string text, RenderContext& r, function<void(int)> callback);
};

#endif