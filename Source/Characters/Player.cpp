#include "Player.h"
#include "../Base/game.h"
#include "../Base/Window.h"
#include "../Maps/Room.h"
#include "../Maps/Map.h"
#include "../Objects/PickableObject.h"
#include "../Maps/GameOverMenu.h"
#include "../Objects/Wearable.h"
#include "Monsters/Fireball.h"

Player::Player(RenderContext& renderer, int lives, int attack, int defense, int startHealth, int startMoney, int startExp) :
	LivingEntity(startHealth, startMoney, startExp, defense), MovingEntity(0, 0, renderer, "player"),
	lives(lives), attack(attack), infosX(SZ_MAINWIDTH), infosY(0), hoverObj(nullptr),
	attackDelay(500), lastAttackTime(0), story(NULL), currentMouseData(MOUSE_DATA())
{
	heart = renderer.LoadTexture("heart");

	inventoryY = new int(0);

	nbPerLine = SZ_INFOSWIDTH / SZ_BLOCKSIZE;
}

void Player::setTextureTag(string tag, bool enabled)
{
	textureTags[tag] = enabled;
}

void Player::updateTexture(RenderContext& renderer)
{
	resetTexture();
	//first we cook the texture from texture tags
	for (auto& entry : textureTags)
	{
		if (entry.second)
		{
			texture += entry.first;
		}
	}
	DrawableEntity::updateTexture(renderer);
}

void Player::resetTexture()
{
	texture = "player";
}


void Player::render(RenderContext& renderer, int offsetX, int offsetY) const
{
	int xx = (x + offsetX) * SZ_BLOCKSIZE;
	int yy = (y + offsetY) * SZ_BLOCKSIZE;
	loadedTx->render(renderer, xx, yy, SZ_BLOCKSIZE, SZ_BLOCKSIZE);
	//DrawableEntity::render(renderer, offsetX, offsetY);
	drawHealthBar(renderer, xx, yy - 5);
	renderInventory(renderer, xx, yy);
}

bool Player::isAlive() const
{
	return lives > 0 || LivingEntity::isAlive();
}

void Player::renderInventory(RenderContext& renderer, int xx, int yy) const
{
	/*Infos*/
	xx = infosX;
	yy = infosY;

	for (int i = 0; i < lives; i++)
	{
		if (xx >= infosX + SZ_INFOSWIDTH)
		{
			xx = infosX;
			yy += heart->getHeight();
		}
		heart->renderUnscaled(renderer, xx, yy);
		xx += heart->getWidth();
	}

	yy += heart->getHeight();
	xx = infosX;
	Texture* tmp = renderer.LoadString(to_string(experience) + " EXP", 0xCEB600FF);
	tmp->renderUnscaled(renderer, xx, yy);
	yy += tmp->getHeight();
	tmp = renderer.LoadString(to_string(money) + " Gold", 0xDDDD00FF);
	tmp->renderUnscaled(renderer, xx, yy);
	tmp = renderer.LoadString("ATK " + to_string(attack), 0xFF9999FF);
	tmp->renderUnscaled(renderer, xx, yy += tmp->getHeight());
	tmp = renderer.LoadString("DEF " + to_string(defense), 0x99FF99FF);
	tmp->renderUnscaled(renderer, xx, yy += tmp->getHeight());
	yy += tmp->getHeight() + SZ_BLOCKSIZE;

	tmp = renderer.LoadString("Collected stuff", 0xFFFFFFFF);
	tmp->renderUnscaled(renderer, xx, yy);

	xx = infosX;
	yy += tmp->getHeight();

	*inventoryY = yy;

	/*The inventory*/
	for (auto& entry : inventoryCases)
	{
		entry.second->sideRender(renderer, xx + (entry.first % nbPerLine) * SZ_BLOCKSIZE, yy + (entry.first / nbPerLine) * SZ_BLOCKSIZE);
	}

	yy += SZ_BLOCKSIZE * (inventoryCases.size() / nbPerLine+1);
	xx = infosX;

	if (hoverObj != nullptr)
		//Draw the info tip of the object
		renderer.LoadText(hoverObj->getInfo(), 0x6B63FFFF, 0, SZ_INFOSWIDTH, 5)
		->renderUnscaled(renderer, xx, yy);
}

/*
Game over if no lives left.
*/
void Player::kill()
{
	if (lives == 0)
	{
		health = 0;
	}
	else
	{
		lives--;
		health = maxHealth;
	}
}

Player::~Player()
{
	clearInventory();

	delete inventoryY;
}

void Player::tick(int time, GAME* game)
{
	if (lives == 0 && !isAlive())
	{
		animateGameOver(time, game);
	}

	if (story != NULL)
	{
		story->tick(time, game);
	}

	//Release the objects pending to be thrown away
	if (objectToRelease.size() > 0)
	{
		for (Object* o : objectToRelease)
		{
			releaseObject(o, game);
		}
		objectToRelease.clear();
	}
}

void Player::animateGameOver(int time, GAME* game)
{
	static int steps;
	static int i;
	static int j;
	static int s;
	static int t = 0;
	if (t == 0) {
		steps = 4 * max(game->currentMap->getCurrentRoomObject().getH(), game->currentMap->getCurrentRoomObject().getW());
		i = x;
		j = y;
		s = 1;
		for (int n = 0; n < game->currentMap->getRoomCount(); n++)
		{
			if (n != game->currentMap->getCurrentRoom())
			{
				game->currentMap->getRooms()[n]->setDiscovered(false);
			}
		}
	}

	if (t < steps)
	{
		switch (t % 4)
		{
		case 0://to the right
			for (int k = 0; k < s; k++)
			{
				i++;
				game->currentMap->getCurrentRoomObject().replaceBlock(new Block(i, j, "empty", *(game->renderer)));
			}
			break;
		case 1://downwards
			s++;
			for (int k = 0; k < s; k++)
			{
				j++;
				game->currentMap->getCurrentRoomObject().replaceBlock(new Block(i, j, "empty", *(game->renderer)));
			}
			break;
		case 2://to the left
			for (int k = 0; k < s; k++)
			{
				i--;
				game->currentMap->getCurrentRoomObject().replaceBlock(new Block(i, j, "empty", *(game->renderer)));
			}
			break;
		case 3://upwards
			s++;
			for (int k = 0; k < s; k++)
			{
				j--;
				game->currentMap->getCurrentRoomObject().replaceBlock(new Block(i, j, "empty", *(game->renderer)));
			}
			break;
		default:
			break;
		}
		t++;
	}
	else
	{
		t = 0;
		lives++;
		//In case of GameOver, the map is destroyed (only case)
		destroyMap(game->worldName, *(game->currentMapId));
		if (isLoaded("Game Over", 0))
		{
			changeMap(game, "Game Over", 0);
		}
		else
		{
			*(game->currentMapId) = 0;
			game->worldName = "Game Over";
			game->currentMap = new GameOverMenu(*this, game);
		}
	}
}

void Player::clearInventory()
{
	list<const Object*> toDel;
	for (auto& entry : inventory)
	{
		toDel.push_back(entry.first);
	}
	inventory.clear();

	for (const Object* o : toDel)
		delete o;
}

void Player::onMouseEvent(MOUSE_DATA* md)
{
	currentMouseData = *md;

	bool found = false;
	bool foundToDel = false;
	if (!inventoryCases.empty() && currentMouseData.x > SZ_MAINWIDTH)
	{
		int pos = /*line*/ (currentMouseData.y - *inventoryY) / SZ_BLOCKSIZE * nbPerLine
			+ (currentMouseData.x - infosX) / SZ_BLOCKSIZE;


		if (inventoryCases.find(pos) != inventoryCases.end())
		{

			if (currentMouseData.state == MouseStateReleased && currentMouseData.button == MouseRight)
			{
				//we remove it from our inventory
				Object* toR = const_cast<Object*>(inventoryCases[pos]); //This is a correct cast because we remove it from the map 3 lines later
				if (toR != nullptr)
				{
					objectToRelease.push_back(toR);
					inventoryCases[pos] = nullptr;
				}
				foundToDel = true;
			}
			else if (currentMouseData.state == MouseStateReleased && currentMouseData.button == MouseLeft)
			{
				//We wear it, only if it is a wearable of course
				const Wearable* wObj = dynamic_cast<const Wearable*>(inventoryCases[pos]);
				if (wObj != nullptr)
					wObj->equip(this);
			}

			if (!foundToDel)
			{
				//we show its infotip
				/**
				* Correct cast :
				* Proof.
				* The reason why objects are const pointers in this map is because they are map::key
				* in another map (inventory). To set the value hoverObj we *must*  bypass the compiler
				* but we won't do anything to the object behind the pointer other than getting info from it
				* (no modification / no deleting).
				* Qed.
				*/
				hoverObj = const_cast<Object*>(inventoryCases[pos]);
				found = true;
			}
		}
	}

	if (!found)
		hoverObj = nullptr;//reset in case the mouse is not hovering any object.
}



void Player::onKeyDown(GAME* game)
{
	if (!isAlive()) return;
	Room& room = game->currentMap->getCurrentRoomObject();

	int curX = x;
	int curY = y;

	switch (game->key)
	{
	case Up:
		curY--;
		break;
	case Left:
		curX--;
		break;
	case Right:
		curX++;
		break;
	case Down:
		curY++;
		break;
	case A:
		//TODO Jump ?
		break;
	case B:
		//Atk
		attackMonsters(room);
		break;
	default:
		break;
	}

	if (curX != x || curY != y)
		room.tryTeleportAt(*this, curX, curY);


#ifdef DEBUG_MODE
	if (game->keyLetter == 'F')
		room.addMonster(new Fireball(*(game->renderer), *this, &room));
	else if (game->keyLetter == 'S')
		room.addObject(new Sword("sw" + to_string(GetRandom(2598)), 5, 5, *(game->renderer), 23));
	else if (game->keyLetter == 'M')
		room.addObject(new Coin("$1", 5, 5, *(game->renderer), 500));
#endif

	if (story != NULL)
	{
		story->onKeyDown(game);
	}
}


void Player::attackMonsters(Room& room)
{
	int t = GetTime();
	if (t - lastAttackTime >= attackDelay)
	{
		lastAttackTime = GetTime();
		for (Monster* m : room.getMonsters())
		{
			if (isInAttackRange(m->getX(), m->getY()))
			{
				m->damage(attack);
			}
		}
	}
}

void Player::gainExperience(int exp)
{
	experience += exp;
}

void Player::gainCoins(int n)
{
	money += n;
}

bool Player::isInAttackRange(int mx, int my)
{
	return abs(x - mx) < 2 && abs(y - my) < 2;
}

int Player::getAttack()
{
	return attack;
}

void Player::addAttack(int toAdd)
{
	if (attack + toAdd >= 0)
		attack += toAdd;
}

int Player::getLives()
{
	return lives;
}

void Player::pickUpObject(const PickableObject* obj, int count)
{
	if (inventory.find(obj) == inventory.end())
	{
		inventory[obj] = 0;
	}

	inventory[obj] += count;
	rebuildInventoryCases();
	obj->onPickup(this);
}

void Player::releaseObject(Object* obj, GAME* game)
{
	game->currentMap->getCurrentRoomObject().addObject(obj, x, y);

	Wearable* w = dynamic_cast<Wearable*>(obj);
	if (w != nullptr)
	{
		//This is a wearable object, do we wear it now?
		if (w->isWorn(this))
			w->remove(this); //yes, so we remove it.
	}
	inventory.erase(obj);

	rebuildInventoryCases();
}

void Player::wearObject(const Wearable* wObj)
{
	wObj->equip(this);
}

bool Player::isWearingSomethingAt(string emplacement, const Wearable* wObj) const
{
	auto w = objectsInHand.find(emplacement);
	if (w != objectsInHand.end())
	{
		return wObj == w->second;
	}
	else
	{
		return false;
	}
}

void Player::rebuildInventoryCases()
{
	inventoryCases.clear();
	int i = 0;
	for (auto& entry : inventory)
	{
		inventoryCases[i] = entry.first;
		i++;
	}
}

void Player::addObjectToWear(string emplacement, const Wearable* wObj)
{
	/*if something is already there, we call its remove method prior to replacing it.*/
	if (objectsInHand.find(emplacement) != objectsInHand.end())
		objectsInHand[emplacement]->remove(this);

	objectsInHand[emplacement] = wObj;
}

void Player::deleteWornObject(string emplacement)
{
	if (objectsInHand.find(emplacement) != objectsInHand.end())
	{
		objectsInHand.erase(emplacement);
	}
}



bool Player::hasObject(string objId)
{
	for (auto& entry : inventory)
	{
		if (entry.first->getId() == objId && entry.second > 0)
			return true;
	}
	return false;
}

bool Player::hasObject(Object* obj)
{
	auto search = inventory.find(obj);
	return (search != inventory.end() && search->second > 0);
}

string Player::inventoryToString() const
{
	string encoding = "";
	for (auto& entry : inventory)
	{
		encoding += "(";
		encoding += entry.first->objectToString();//todo include quantity of each object.
		encoding += ") ";
		encoding += to_string(entry.second);
		encoding += " ";
	}
	return encoding;
}

void Player::setLives(int l)
{
	lives = l;
}

void Player::initialise(string headerline, RenderContext& renderer)
{
	/* The player's initial information is composed of its initial characteristics followed by its inventory. */
	size_t a = headerline.find('(');
	if (a == -1)
	{
		a = headerline.length();
	}
	string characteristics = headerline.substr(0, a), inventoryContents = headerline.substr(a);
	/*
	The player's characteristics are, in order : health, number of lives, coins, experience, maximum health per life.
	We need to keep in mind that they are not all necessarily present, and that some may be worth "X" in which case we need to set it to the default value.
	*/
	int maxChar = 5;
	auto iss = istringstream{ characteristics };
	string str = "";
	vector<string> tokens;
	while (iss >> str)
	{
		tokens.push_back(str);
	}
	int missing = maxChar - tokens.size();
	for (int i = 0; i < missing; i++)
	{
		tokens.push_back("X");
	}
	Player otherp = Player(renderer); //We create another temporary player which will have the correct default values for each characteristic (except potentially health as it depends on another value).
	if (tokens[0] != "X")
		health = stoi(tokens[0]);
	if (tokens[1] == "X")
		lives = otherp.getLives();
	else
		lives = stoi(tokens[1]);
	if (tokens[2] == "X")
		money = otherp.getMoney();
	else
		money = stoi(tokens[2]);
	if (tokens[3] == "X")
		experience = otherp.getExperience();
	else
		experience = stoi(tokens[3]);
	if (tokens[4] == "X")
		maxHealth = otherp.getMaxHealth();
	else
		maxHealth = stoi(tokens[4]);
	if (tokens[0] == "X")
		health = maxHealth;

	//We clear the inventory and reset the texture, then add the objects one by one.
	objectsInHand.clear();
	textureTags.clear();
	updateTexture(renderer);
	clearInventory();
	resetTexture();
	while (inventoryContents.length() > 0 && inventoryContents[0] == '(')
	{
		size_t nextpar = inventoryContents.find(')');
		string currentObject = inventoryContents.substr(1, nextpar - 1);
		inventoryContents.erase(0, nextpar + 2);
		int uniqueId = 0;
		Object* obj = Map::parseObject(currentObject, renderer, &uniqueId, -1, -1);
		try
		{
			pickUpObject((PickableObject*)obj, stoi(inventoryContents, &a));
			inventoryContents.erase(0, a + 1);
		}
		catch (...)
		{
			pickUpObject((PickableObject*)obj);
		}
	}

	rebuildInventoryCases();
}

void Player::setStory(Story* s)
{
	if (story != NULL)
		clearStory();
	story = s;
}

void Player::clearStory()
{
	if (story != NULL)
		delete story;
	story = NULL;
}

bool Player::hasStory()
{
	return (story != NULL);
}

Story& Player::getStory() const
{
	return *story;
}
