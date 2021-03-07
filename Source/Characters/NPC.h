#ifndef NPC_H
#define NPC_H

#include "../Objects/Object.h"
#include <functional>
#include "../Interactions/Button.h"
#include <list>
#include "Player.h"

class Map;

/// <summary>
/// An NPC is a MovingEntity that is a Non-Player Character, who can talk to the Player and offer him choices
/// in the Story. An NPC is considered as an Object due to its lack of movement, attacking, and health.
/// </summary>
class NPC : public Object
{
protected:
	/// <summary>
	/// The part of dialog to load from Res/Text and give to the player when it approaches.
	/// </summary>
	string speech;

	/// <summary>
	/// The name of the NPC to load from Res/Text and give to the player when it approaches.
	/// </summary>
	string name;

	/// <summary>
	/// Buffered texture to draw in infos section.
	/// </summary>
	Texture* text;

	/// <summary>
	/// Different clickable choices at the bottom of the dialog.
	/// </summary>
	list<Button*> choices;

	/// <summary>
	/// Allows to add mouse events handlers only the first time the NPC object gets updated.
	/// </summary>
	bool signedInForEvents;

	void setTexture(RenderContext& renderer);

	Map* container;
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="identifier"></param>
	/// <param name="speech"></param>
	/// <param name="posx"></param>
	/// <param name="posy"></param>
	/// <param name="tx"></param>
	/// <param name="renderer"></param>
	/// <param name="trav"></param>
	NPC(string identifier, string name, string speech, int posx, int posy, string tx, RenderContext& renderer, Map* map, bool trav);

	virtual ~NPC();

	/// <summary>
	/// The following function describes how each type of object interacts with the player.
	/// Returns true if the object has been picked up (thus informing that we should remove it from the room)
	/// </summary>
	/// <param name="game"></param>
	virtual bool updateObject(GAME* game);

	/// <summary>
	/// Indicates whether the player is in the action radius of the NPC
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	inline bool isPlayerNearby(Player* p)
	{
		return abs(x - p->getX()) < 2 && abs(y - p->getY()) < 2;
	}

	/// <summary>
	/// Adds a choice in the dialog (to branch on another part of the story, or anything else).
	/// </summary>
	/// <param name="text"></param>
	/// <param name="r"></param>
	/// <param name="callback"></param>
	void addChoice(string text, RenderContext& r, function<void(int)> callback);

	/// <summary>
	/// Adds directly a button, at the right location.
	/// </summary>
	/// <param name="button"></param>
	void addChoice(Button* button);
	/// <summary>
	/// We encode an NPC with its id, its name, and its speech.
	/// </summary>
	string objectToString();
};

#endif
