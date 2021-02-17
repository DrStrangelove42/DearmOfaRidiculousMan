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

class Room;
class Map;
class Object;
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
protected:
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
	/// 
	/// </summary>
	unordered_map<string, Wearable*> objectsInHand;

	/// <summary>
	/// This one is ordered. In order to add different modifying tags to the texture, it must be
	/// ordered (so that when you add 'toto', there is only one way it blends with e.g. 'sword' : swordtoto or shieldswordtoto but not totosword...)
	/// </summary>
	map<string, bool> textureTags;
public:
	~Player();
	
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
	Player(RenderContext& renderer, int lives = 3, int attack = 5, int defense = 0, int startHealth = 100, int startMoney = 0, int startExp = 0);

	 

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
	/// Rendering management of the right panel
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="xx"></param>
	/// <param name="yy"></param>
	void renderInventory(RenderContext& renderer, int xx, int yy) const;

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
	void pickUpObject(const  Object* obj, RenderContext& r, int count = 1);

	/// <summary>
	/// Calls the equip method of the object.
	/// </summary>
	/// <param name="wObj"></param>
	void wearObject(Wearable* wObj);

	/// <summary>
	/// Returns whether the emplacement is taken.
	/// </summary>
	/// <param name="emplacement"></param>
	/// <returns></returns>
	bool isWearingSomethingAt(string emplacement);

	/// <summary>
	/// Fill the emplacement (or switch) with the specified object.
	/// </summary>
	/// <param name="emplacement"></param>
	/// <param name="wObj"></param>
	void addObjectToWear(string emplacement, Wearable* wObj);

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
	/// Encodes the player's inventory.
	/// </summary>
	string inventoryToString() const;

	/// <summary>
	/// Sets the number of lives of the player to l.
	/// </summary>
	/// <param name="l"></param>
	void setLives(int l);

	void initialise(string headerline, RenderContext& renderer);

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
};

#endif
