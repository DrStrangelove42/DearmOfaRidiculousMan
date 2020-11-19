#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "../Base/Entity.h"
#include "../Base/utils.h"
#include "../Base/config.h"
#include "../Items/item.h"
#include "MovingEntity.h"
#include "LivingEntity.h"
#include <unordered_map>

/*
The Player object is the representation of the person
playing the game.
*/
class Player : public MovingEntity, public LivingEntity
{
protected:

	/* Number of lives until game over. */
	int lives;
	/* How much damage the player deals when attacking. */
	int attack;
	/* How much damage can a player absorb when being attacked. */
	int defense;
	/* Player's items */
	unordered_map <string, int> items; //int is how many of that type of item player has (eg might have several times the same potion)
	/* The texture used for the player. */
	Texture* texture;

public:
	~Player() {};
	/* Creates the player */
	Player(RenderContext& renderer, int lives = 1, int attack = 5, int defense = 0, int startHealth = 100, int startMoney = 0, int startExp = 0);

	virtual void kill();

	/* Rendering management */
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0);

	/* Time management */
	virtual void tick(int time, RenderContext& r);

	virtual void getExperience(int exp);
	virtual void getCoins(int n);

	bool isInAttackRange(int, int);
	int getAttack();
	int getDefense();

	/* Adds count times the item to a player's inventory. */
	void pickUpItem(Item item, int count = 1);

	/* Tells us whether the player has a particular item or not. */
	bool hasItem(string itemId);
	bool hasItem(Item item);
};

#endif
