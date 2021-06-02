#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "../Base/utils.h"
#include "../Base/config.h"
#include "../Interactions/Story.h"
#include "MovingEntity.h"
#include "LivingEntity.h"
#include <unordered_map>
#include "../Objects/Sign.h"
#include "../Objects/Coin.h"

class Room;
class Map;
class Object;
class PickableObject;
class Wearable;

/// <summary>
/// The Player is an Entity that represents the person
/// playing the game.
/// </summary>
class Player : public MovingEntity, public LivingEntity
{
private:
	/// <summary>
	/// Time of last attack, used for attack delay.
	/// </summary>
	int lastAttackTime;

	/// <summary>
	/// Number of inventory objets in one line, computed at the creation of the Player
	/// Here we assume that the metrics (config.h) will not change during a game.
	/// </summary>
	int nbPerLine;

	/// <summary>
	/// Graphical y coordinate of the inventory.
	/// </summary>
	int* inventoryY;

	/// <summary>
	/// The message queue containing the informations about the game to display on the screen.
	/// The int is to make the old ones disappear after the correct amount of time.
	/// </summary>
	unordered_map<string, int> messages;
	/// <summary>
	/// The buffered textures
	/// </summary>
	unordered_map<string, AnimatedTexture*> * messagesBuffer;

	//Visual effects for messages
	list<int> fg;
	list<int> bg;
protected:
	/// <summary>
	/// Object under the mouse cursor, for rendering purposes
	/// </summary>
	Object* hoverObj;

	/// <summary>
	/// Number of lives until game over.
	/// </summary>
	int lives;

	/// <summary>
	/// How much damage the player deals when attacking.
	/// </summary>
	int attack;

	/// <summary>
	/// Player's items
	/// int is how many of that type of item player has (eg might have several times the same potion)
	/// </summary>
	unordered_map<const Object*, int> inventory;

	/// <summary>
	/// The rendered inventory for display purposes : associates a position in the list to an object in the inventory.
	/// </summary>
	unordered_map<int, const Object*> inventoryCases;

	/// <summary>
	/// Horizontal offset of the infos sub window
	/// </summary>
	int infosX;

	/// <summary>
	/// Vertical offset of the infos sub window
	/// </summary>
	int infosY;

	/// <summary>
	/// Minimal amount of time between attacks, in ticks 
	/// </summary>
	int attackDelay;

	/// <summary>
	/// A Heart texture for player lives.
	/// </summary>
	Texture* heart;

	/// <summary>
	/// The story object (used in story mode).
	/// </summary>
	Story* story;

	/// <summary>
	/// All the objects that the player is currently wearing.
	/// </summary>
	unordered_map<string, const Wearable*> objectsInHand;

	/// <summary>
	/// The additional textures used to display the player (for instance to show weapons, hats, ...).
	/// In order to add different modifying tags to the texture, this map must be
	/// ordered (so that when you add 'toto', there is only one way it blends with e.g. 'sword' : swordtoto or shieldswordtoto but not totosword...)
	/// </summary>
	map<string, bool> textureTags;

	/// <summary>
	/// The objects that the user wants to throw away.
	/// </summary>
	list<Object*> objectToRelease;

	/// <summary>
	/// Current informations of the mouse.
	/// </summary>
	MOUSE_DATA currentMouseData;

	/// <summary>
	/// Rendering the log
	/// </summary>
	void renderMessages(RenderContext& renderer) const;


	/// <summary>
	/// Rendering management of the right panel
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="xx"></param>
	/// <param name="yy"></param>
	void renderInventory(RenderContext& renderer, int xx, int yy) const;
public:

	virtual ~Player();

	/// <summary>
	/// Creates the player.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="lives"></param>
	/// <param name="attack"></param>
	/// <param name="defense"></param>
	/// <param name="startHealth"></param>
	/// <param name="startMoney"></param>
	/// <param name="startExp"></param>
	Player(RenderContext& renderer, string saveName, int lives = 3, int attack = 5, int defense = 0, int startHealth = 100, int startMoney = 0, int startExp = 0);

	/// <summary>
	/// Instant kill.
	/// </summary>
	virtual void kill();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="tag"></param>
	/// <param name="enabled"></param>
	void setTextureTag(string tag, bool enabled);

	/// <summary>
	/// Forces the object to reload the <see cref="Texture">Texture</see> corresponding to the current ID in <texture>.
	/// Note that there is no function to change the <see cref="Texture">Texture</see> from outside of the object, because we
	/// don't want to, for now.
	/// </summary>
	/// <param name="renderer"></param>
	virtual void updateTexture(RenderContext& renderer);

	/// <summary>
	/// Sets the texture ID to the default one.
	/// </summary>
	virtual void resetTexture();

	/// <summary>
	/// Rendering management
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0) const;

	/// <summary>
	/// The player can have a health of zero and still have lives left.
	/// </summary>
	/// <returns></returns>
	virtual bool isAlive() const;


	/// <summary>
	/// Time management
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	virtual void tick(int time, GAME* game);

	/// <summary>
	/// Game over animation when the player is dead.
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	void animateGameOver(int time, GAME* game);

	/// <summary>
	/// Deletes all the objects in the inventory.
	/// </summary>
	void clearInventory();

	/// <summary>
	/// <see cref="MOUSE_DATA">Mouse event</see>.
	/// </summary>
	/// <param name="md"></param>
	virtual void onMouseEvent(MOUSE_DATA* md);

	/// <summary>
	/// When a key is pushed on the keyboard.
	/// </summary>
	/// <param name="ea"></param>
	virtual void onKeyDown(GAME* game);

	/// <summary>
	/// Attacks all the monsters in the room that are in attacking range of the player. 
	/// </summary>
	void attackMonsters(Room&);

	/// <summary>
	/// Gives experience to the player.
	/// </summary>
	/// <param name="exp"></param>
	virtual void gainExperience(int exp);

	/// <summary>
	/// Gives coins to the player.
	/// </summary>
	/// <param name="n"></param>
	virtual void gainCoins(int n);

	/// <summary>
	/// Returns a boolean indicating whether the player can attack the monster in position (mx,my)
	/// </summary>
	/// <param name="mx"></param>
	/// <param name="my"></param>
	/// <returns></returns>
	bool isInAttackRange(int mx, int my);

	/// <summary>
	/// Returns player's attack value.
	/// </summary>
	/// <returns></returns>
	int getAttack();

	/// <summary>
	/// Adds the specified amount to the attack value.
	/// </summary>
	/// <param name="toAdd"></param>
	/// <returns></returns>
	void addAttack(int toAdd);

	/// <summary>
	/// Returns player's number of lives.
	/// </summary>
	/// <returns></returns>
	int getLives();

	/// <summary>
	/// Adds count times the item to a player's inventory.
	/// </summary>
	/// <param name="item"></param>
	/// <param name="count"></param>
	void pickUpObject(const  PickableObject* obj, int count = 1);

	/// <summary>
	/// releases the object on the map at the current position.
	/// </summary>
	void releaseObject(Object* obj, GAME* game);

	/// <summary>
	/// Recomputes the list of cases from the current inventory.
	/// </summary>
	void rebuildInventoryCases();

	/// <summary>
	/// Calls the equip method of the object.
	/// </summary>
	/// <param name="wObj"></param>
	void wearObject(const Wearable* wObj);

	/// <summary>
	/// Returns whether the emplacement is taken.
	/// </summary>
	/// <param name="emplacement"></param>
	/// <returns></returns>
	bool isWearingSomethingAt(string emplacement, const Wearable* wObj) const;

	/// <summary>
	/// Fill the emplacement (or switch) with the specified object.
	/// </summary>
	/// <param name="emplacement"></param>
	/// <param name="wObj"></param>
	void addObjectToWear(string emplacement, const Wearable* wObj);

	/// <summary>
	/// Removes any object from the specified emplacement, if it is there.
	/// </summary>
	/// <param name="emplacement"></param>
	void deleteWornObject(string emplacement);

	/// <summary>
	/// Tells us whether the player has a particular item or not.
	/// </summary>
	/// <param name="itemId"></param>
	/// <returns></returns>
	bool hasObject(string objId);

	/// <summary>
	/// Tells us whether the player has a particular item or not.
	/// </summary>
	/// <param name="item"></param>
	/// <returns></returns>
	bool hasObject(Object* obj);

	/// <summary>
	/// Sets the number of lives of the player to l.
	/// </summary>
	/// <param name="l"></param>
	void setLives(int l);

	/// <summary>
	/// Initialises the player with the information encoded in the headerline.
	/// </summary>
	void initialise(ifstream& saveFile, RenderContext& renderer);

	/// <summary>
	/// Saves the player's info in the save file corresponding to saveName.
	/// </summary>
	void save(string& saveFile);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="story"></param>
	void setStory(Story* s);

	/// <summary>
	/// 
	/// </summary>
	void clearStory();

	bool hasStory();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Story& getStory() const;

	/// <summary>
	/// Display a text message for a short period of time on the screen.
	/// </summary>
	/// <param name="message"></param>
	/// <returns></returns>
	void logMessage(string message);


};

#endif
