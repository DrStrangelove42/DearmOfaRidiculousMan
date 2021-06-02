[1mdiff --git a/Source/Base/config.cpp b/Source/Base/config.cpp[m
[1mindex 8baceea..4859916 100644[m
[1m--- a/Source/Base/config.cpp[m
[1m+++ b/Source/Base/config.cpp[m
[36m@@ -55,6 +55,8 @@[m [mstring WORLDDATA_LOCATION = DATA_LOCATION + "Data/Worlds/";[m
 [m
 string SAVES_LOCATION = DATA_LOCATION + "Data/Saves/";[m
 [m
[32m+[m[32mstring SAVES_CURRENT = "default";[m
[32m+[m
 string LANGFILES_EXT = ".txt";[m
 string LANG_LOCATION = DATA_LOCATION + "Res/Text/";[m
 string LANGUAGE = "en-uk";[m
\ No newline at end of file[m
[1mdiff --git a/Source/Base/config.h b/Source/Base/config.h[m
[1mindex 0578d1d..05564f0 100644[m
[1m--- a/Source/Base/config.h[m
[1m+++ b/Source/Base/config.h[m
[36m@@ -109,6 +109,11 @@[m [mextern string WORLDDATA_LOCATION;[m
 /// </summary>[m
 extern string SAVES_LOCATION;[m
 [m
[32m+[m[32m/// <summary>[m
[32m+[m[32m/// Current save name.[m
[32m+[m[32m/// </summary>[m
[32m+[m[32mextern string SAVES_CURRENT;[m
[32m+[m
 /// <summary>[m
 /// Absolute path to the data folder. This must have a trailing slash.[m
 /// </summary>[m
[1mdiff --git a/Source/Characters/Player.cpp b/Source/Characters/Player.cpp[m
[1mindex 97300a1..93dadf8 100644[m
[1m--- a/Source/Characters/Player.cpp[m
[1m+++ b/Source/Characters/Player.cpp[m
[36m@@ -8,7 +8,7 @@[m
 #include "../Objects/Wearable.h"[m
 #include "Monsters/Fireball.h"[m
 [m
[31m-Player::Player(RenderContext& renderer, int lives, int attack, int defense, int startHealth, int startMoney, int startExp) :[m
[32m+[m[32mPlayer::Player(RenderContext& renderer, string saveName, int lives, int attack, int defense, int startHealth, int startMoney, int startExp) :[m
 	LivingEntity(startHealth, startMoney, startExp, defense), MovingEntity(0, 0, renderer, "player"),[m
 	lives(lives), attack(attack), infosX(SZ_MAINWIDTH), infosY(0), hoverObj(nullptr),[m
 	attackDelay(500), lastAttackTime(0), story(NULL), currentMouseData(MOUSE_DATA())[m
[36m@@ -23,6 +23,19 @@[m [mPlayer::Player(RenderContext& renderer, int lives, int attack, int defense, int[m
 	bg = CreateFade(0x000000FF, 0x00000000, 10, 40);[m
 [m
 	messagesBuffer = new unordered_map<string, AnimatedTexture*>();[m
[32m+[m
[32m+[m	[32m/* Loading player informations from a save file */[m
[32m+[m	[32mif (saveName != "") //No save name = default values[m
[32m+[m	[32m{[m
[32m+[m		[32mstring savePlayerPath = SAVES_LOCATION + saveName + "/" + "Start" + EXT;[m
[32m+[m		[32mstruct stat l;[m
[32m+[m		[32mif (stat(savePlayerPath.c_str(), &l) == 0)[m
[32m+[m		[32m{[m
[32m+[m			[32mifstream infos(savePlayerPath);[m
[32m+[m			[32minitialise(infos, renderer);[m
[32m+[m			[32minfos.close();[m
[32m+[m		[32m}[m
[32m+[m	[32m}[m
 }[m
 [m
 void Player::setTextureTag(string tag, bool enabled)[m
[36m@@ -524,27 +537,21 @@[m [mbool Player::hasObject(Object* obj)[m
 	return (search != inventory.end() && search->second > 0);[m
 }[m
 [m
[31m-string Player::inventoryToString() const[m
[31m-{[m
[31m-	string encoding = "";[m
[31m-	for (auto& entry : inventory)[m
[31m-	{[m
[31m-		encoding += "(";[m
[31m-		encoding += entry.first->objectToString();//todo include quantity of each object.[m
[31m-		encoding += ") ";[m
[31m-		encoding += to_string(entry.second);[m
[31m-		encoding += " ";[m
[31m-	}[m
[31m-	return encoding;[m
[31m-}[m
[31m-[m
 void Player::setLives(int l)[m
 {[m
 	lives = l;[m
 }[m
 [m
[31m-void Player::initialise(string headerline, RenderContext& renderer)[m
[32m+[m[32mvoid Player::initialise(ifstream& saveFile, RenderContext& renderer)[m
 {[m
[32m+[m	[32mif (!saveFile.is_open()) {[m
[32m+[m		[32mcerr << "Could not open the file to load player info." << endl;[m
[32m+[m		[32mreturn;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mstring headerline;[m
[32m+[m	[32mgetline(saveFile, headerline);[m
[32m+[m
 	/* The player's initial information is composed of its initial characteristics followed by its inventory. */[m
 	size_t a = headerline.find('(');[m
 	if (a == -1)[m
[36m@@ -569,34 +576,43 @@[m [mvoid Player::initialise(string headerline, RenderContext& renderer)[m
 	{[m
 		tokens.push_back("X");[m
 	}[m
[31m-	Player otherp = Player(renderer); //We create another temporary player which will have the correct default values for each characteristic (except potentially health as it depends on another value).[m
[32m+[m	[32mPlayer otherp = Player(renderer, ""); //We create another temporary player which will have the correct default values for each characteristic (except potentially health as it depends on another value).[m
 	if (tokens[0] != "X")[m
 		health = stoi(tokens[0]);[m
[32m+[m
 	if (tokens[1] == "X")[m
 		lives = otherp.getLives();[m
 	else[m
 		lives = stoi(tokens[1]);[m
[32m+[m
 	if (tokens[2] == "X")[m
 		money = otherp.getMoney();[m
 	else[m
 		money = stoi(tokens[2]);[m
[32m+[m
 	if (tokens[3] == "X")[m
 		experience = otherp.getExperience();[m
 	else[m
 		experience = stoi(tokens[3]);[m
[32m+[m
 	if (tokens[4] == "X")[m
 		maxHealth = otherp.getMaxHealth();[m
 	else[m
 		maxHealth = stoi(tokens[4]);[m
[32m+[m
 	if (tokens[0] == "X")[m
 		health = maxHealth;[m
 [m
 	//We clear the inventory and reset the texture, then add the objects one by one.[m
[31m-	objectsInHand.clear();[m
[32m+[m	[32mobjectsInHand.clear();//no need to call Wearable::remove, because the informations are resetted anyway.[m
 	textureTags.clear();[m
 	updateTexture(renderer);[m
 	clearInventory();[m
 	resetTexture();[m
[32m+[m
[32m+[m	[32mmap<int, Object*> revIdx;[m
[32m+[m	[32mint i = 0;[m
[32m+[m
 	while (inventoryContents.length() > 0 && inventoryContents[0] == '(')[m
 	{[m
 		size_t nextpar = inventoryContents.find(')');[m
[36m@@ -613,9 +629,65 @@[m [mvoid Player::initialise(string headerline, RenderContext& renderer)[m
 		{[m
 			pickUpObject((PickableObject*)obj);[m
 		}[m
[32m+[m		[32mrevIdx[i] = obj;[m
[32m+[m		[32mi++;[m
 	}[m
 [m
 	rebuildInventoryCases();[m
[32m+[m	[32mstring curPlace;[m
[32m+[m	[32mint curI;[m
[32m+[m
[32m+[m	[32m//Load the objects in hand, with the help of the reversed index above.[m
[32m+[m	[32mwhile (getline(saveFile, headerline))[m
[32m+[m	[32m{[m
[32m+[m		[32mcurPlace = EatToken(headerline, ':');[m
[32m+[m
[32m+[m		[32mcurI = stoi(headerline);[m
[32m+[m
[32m+[m		[32m//Objects that are saved as references in this section implement Wearable by definition.[m
[32m+[m		[32mstatic_cast<Wearable*>(revIdx[curI])->equip(this);[m
[32m+[m	[32m}[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mvoid Player::save(string& saveName)[m
[32m+[m[32m{[m
[32m+[m	[32m//Inventory and player info[m
[32m+[m	[32mofstream PlayerData(SAVES_LOCATION + saveName + "/" + "Start" + EXT);[m
[32m+[m	[32m//PlayerData << mapNumber << " " << roomNumber << " " << p.getX() << " " << p.getY() << endl;  : no more position information.[m
[32m+[m
[32m+[m	[32m//Object address -> its index in the list, to retrieve which is which when loading to fill hands.[m
[32m+[m	[32munordered_map<const Object*, int> idx;[m
[32m+[m
[32m+[m	[32mstring inven = "";[m
[32m+[m	[32mint i = 0;[m
[32m+[m
[32m+[m	[32mfor (auto& entry : inventory)[m
[32m+[m	[32m{[m
[32m+[m		[32minven += "(";[m
[32m+[m		[32minven += entry.first->objectToString();//todo include quantity of each object.[m
[32m+[m		[32minven += ") ";[m
[32m+[m		[32minven += to_string(entry.second);[m
[32m+[m		[32minven += " ";[m
[32m+[m		[32midx[entry.first] = i;[m
[32m+[m		[32mi++;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mPlayerData << getHealth() << " " <<[m
[32m+[m		[32mgetLives() << " " <<[m
[32m+[m		[32mgetMoney() << " " <<[m
[32m+[m		[32mgetExperience() << " " <<[m
[32m+[m		[32mgetMaxHealth() << " " <<[m
[32m+[m		[32minven << endl;[m
[32m+[m
[32m+[m	[32m//Saves the objects that are worn as references in the list above.[m
[32m+[m	[32mfor (auto& entry : objectsInHand)[m
[32m+[m	[32m{[m
[32m+[m		[32mPlayerData << entry.first << ":" << idx[entry.second] << endl;[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mPlayerData.close();[m
[32m+[m
[32m+[m	[32mlogMessage("Progess saved.");[m
 }[m
 [m
 void Player::setStory(Story* s)[m
[36m@@ -659,10 +731,10 @@[m [mvoid Player::renderMessages(RenderContext& renderer) const[m
 {[m
 	int y = 5 * SZ_BLOCKSIZE;//below the map title[m
 	for (auto& e : messages)[m
[31m-	{ [m
[32m+[m	[32m{[m
 		if (messagesBuffer->find(e.first) == messagesBuffer->end())[m
 			(*messagesBuffer)[e.first] = static_cast<AnimatedTexture*>(renderer.LoadAnimatedBoxedString(e.first, fg, bg, 100, false));[m
[31m-		[m
[32m+[m
 		AnimatedTexture* cur = (*messagesBuffer)[e.first];[m
 		cur->renderUnscaled(renderer, 3 * SZ_BLOCKSIZE, y);[m
 		y += cur->getHeight();[m
[1mdiff --git a/Source/Characters/Player.h b/Source/Characters/Player.h[m
[1mindex e86d7e1..715c2ea 100644[m
[1m--- a/Source/Characters/Player.h[m
[1m+++ b/Source/Characters/Player.h[m
[36m@@ -106,7 +106,7 @@[m [mprotected:[m
 	Story* story;[m
 [m
 	/// <summary>[m
[31m-	/// [m
[32m+[m	[32m/// All the objects that the player is currently wearing.[m
 	/// </summary>[m
 	unordered_map<string, const Wearable*> objectsInHand;[m
 [m
[36m@@ -141,6 +141,7 @@[m [mprotected:[m
 	/// <param name="yy"></param>[m
 	void renderInventory(RenderContext& renderer, int xx, int yy) const;[m
 public:[m
[32m+[m
 	virtual ~Player();[m
 [m
 	/// <summary>[m
[36m@@ -153,7 +154,7 @@[m [mpublic:[m
 	/// <param name="startHealth"></param>[m
 	/// <param name="startMoney"></param>[m
 	/// <param name="startExp"></param>[m
[31m-	Player(RenderContext& renderer, int lives = 3, int attack = 5, int defense = 0, int startHealth = 100, int startMoney = 0, int startExp = 0);[m
[32m+[m	[32mPlayer(RenderContext& renderer, string saveName, int lives = 3, int attack = 5, int defense = 0, int startHealth = 100, int startMoney = 0, int startExp = 0);[m
 [m
 	/// <summary>[m
 	/// Instant kill.[m
[36m@@ -327,11 +328,6 @@[m [mpublic:[m
 	/// <returns></returns>[m
 	bool hasObject(Object* obj);[m
 [m
[31m-	/// <summary>[m
[31m-	/// Encodes the player's inventory.[m
[31m-	/// </summary>[m
[31m-	string inventoryToString() const;[m
[31m-[m
 	/// <summary>[m
 	/// Sets the number of lives of the player to l.[m
 	/// </summary>[m
[36m@@ -339,9 +335,14 @@[m [mpublic:[m
 	void setLives(int l);[m
 [m
 	/// <summary>[m
[31m-	/// [m
[32m+[m	[32m/// Initialises the player with the information encoded in the headerline.[m
[32m+[m	[32m/// </summary>[m
[32m+[m	[32mvoid initialise(ifstream& saveFile, RenderContext& renderer);[m
[32m+[m
[32m+[m	[32m/// <summary>[m
[32m+[m	[32m/// Saves the player's info in the save file corresponding to saveName.[m
 	/// </summary>[m
[31m-	void initialise(string headerline, RenderContext& renderer);[m
[32m+[m	[32mvoid save(string& saveFile);[m
 [m
 	/// <summary>[m
 	/// [m
[1mdiff --git a/Source/Maps/Map.cpp b/Source/Maps/Map.cpp[m
[1mindex b556c0e..01ea82d 100644[m
[1m--- a/Source/Maps/Map.cpp[m
[1m+++ b/Source/Maps/Map.cpp[m
[36m@@ -382,13 +382,8 @@[m [mvoid Map::mapFromFiles(string worldName, Player& p, RenderContext& renderer, int[m
 		{[m
 			line = "";[m
 		}[m
[31m-		p.initialise(line, renderer);[m
[31m-[m
[31m-		/*TODO : inventory. The objects generated and given to the player will be encoded[m
[31m-		in the same way as ones in chests, we need to find a way to unify both and to make[m
[31m-		it easier to extend a chest's possibilities (xp, money, life). Some virtual function used here and in chest?*/[m
[31m-[m
 	}[m
[32m+[m
 	start.close();[m
 	ifstream layout(filename + to_string(*startMap) + EXT);[m
 [m
[36m@@ -408,8 +403,6 @@[m [mvoid Map::mapFromFiles(string worldName, Player& p, RenderContext& renderer, int[m
 	rooms[currentRoom]->setDiscovered(true);[m
 [m
 	intlGetDataFromFile(filename, *startMap, renderer, p);[m
[31m-[m
[31m-[m
 }[m
 [m
 void Map::intlGetDataFromFile(string filename, int mapIndex, RenderContext& renderer, Player& p)[m
[36m@@ -419,7 +412,7 @@[m [mvoid Map::intlGetDataFromFile(string filename, int mapIndex, RenderContext& rend[m
 	int uniqueId = 0; // This integer is used to make sure that objects in chests have unique identifiers.[m
 [m
 	/*Is there a saved progress?*/[m
[31m-	string savePath = SAVES_LOCATION + "default/" + worldName + to_string(mapIndex) + "Data" + EXT;[m
[32m+[m	[32mstring savePath = SAVES_LOCATION + SAVES_CURRENT + "/" + worldName + to_string(mapIndex) + "Data" + EXT;[m
 	struct stat l;[m
 	bool fromSave = false;[m
 	if (stat(savePath.c_str(), &l) == 0)[m
[36m@@ -750,14 +743,7 @@[m [mvoid Map::saveProgress(string saveName, string originalWorldName, int mapNumber,[m
 [m
 	SaveData.close();[m
 [m
[31m-	//Inventory and player info[m
[31m-	ofstream PlayerData(SAVES_LOCATION + saveName + "/" + "Start" + EXT);[m
[31m-	PlayerData << mapNumber << " " << roomNumber << " " << p.getX() << " " << p.getY() << endl;[m
[31m-	PlayerData << p.getHealth() << " " << p.getLives() << " " << p.getMoney() << " " << p.getExperience() << " " << p.getMaxHealth() << " " << p.inventoryToString();[m
[31m-	//TODO : Add initial attack and defense of player without objects (default being 5 and 0 respectively)[m
[31m-	PlayerData.close();[m
[31m-[m
[31m-	p.logMessage("Progess saved.");[m
[32m+[m	[32mp.save(saveName);[m
 }[m
 [m
 void Map::sendMonstersToWarp(int x, int y, int destRoom, int destX, int destY)[m
[1mdiff --git a/Source/Objects/Checkpoint.cpp b/Source/Objects/Checkpoint.cpp[m
[1mindex 1388ef4..f776495 100644[m
[1m--- a/Source/Objects/Checkpoint.cpp[m
[1m+++ b/Source/Objects/Checkpoint.cpp[m
[36m@@ -19,7 +19,7 @@[m [mbool Checkpoint::updateObject(GAME* game)[m
 		return false;[m
 	}[m
 	//Enregistrer le contexte actuel[m
[31m-	game->currentMap->saveProgress("default", game->worldName, *(game->currentMapId), game->currentMap->getCurrentRoom(), *(game->player));[m
[32m+[m	[32mgame->currentMap->saveProgress(SAVES_CURRENT, game->worldName, *(game->currentMapId), game->currentMap->getCurrentRoom(), *(game->player));[m
 	[m
 	return true;[m
 }[m
[1mdiff --git a/Source/Objects/VisibleWearable.cpp b/Source/Objects/VisibleWearable.cpp[m
[1mindex 653c235..699f0e4 100644[m
[1m--- a/Source/Objects/VisibleWearable.cpp[m
[1m+++ b/Source/Objects/VisibleWearable.cpp[m
[36m@@ -6,7 +6,7 @@[m [mVisibleWearable::~VisibleWearable()[m
 }[m
 [m
 VisibleWearable::VisibleWearable(string identifier, int posx, int posy, string tag, RenderContext& renderer) :[m
[31m-	PickableObject(identifier, posx, posy, tag, renderer, true),[m
[32m+[m	[32mWearable(identifier, posx, posy, tag, renderer),[m
 	renderer(renderer), tag(tag)[m
 {[m
 [m
[36m@@ -25,11 +25,11 @@[m [mvoid VisibleWearable::remove(Player* p) const[m
 	//disable the tag[m
 	p->setTextureTag(tag, false);[m
 	p->updateTexture(renderer);[m
[31m-}[m
[31m-[m
[31m-bool VisibleWearable::isWorn(Player* p) const[m
[31m-{[m
[31m-	return p->isWearingSomethingAt(tag + "hand", this);[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mbool VisibleWearable::isWorn(Player* p) const[m
[32m+[m[32m{[m
[32m+[m	[32mreturn p->isWearingSomethingAt(tag + "hand", this);[m
 }[m
 [m
 void VisibleWearable::onPickup(Player* p) const[m
[1mdiff --git a/Source/Objects/VisibleWearable.h b/Source/Objects/VisibleWearable.h[m
[1mindex e9681a5..1c6719c 100644[m
[1m--- a/Source/Objects/VisibleWearable.h[m
[1m+++ b/Source/Objects/VisibleWearable.h[m
[36m@@ -2,12 +2,12 @@[m
 #define VWEARABLE_H[m
 [m
 #include "Wearable.h"[m
[31m-#include "PickableObject.h"[m
[32m+[m
 [m
 /// <summary>[m
 /// [m
 /// </summary>[m
[31m-class VisibleWearable : public Wearable, public PickableObject[m
[32m+[m[32mclass VisibleWearable : public Wearable[m
 {[m
 protected:[m
 	RenderContext& renderer;[m
[36m@@ -15,7 +15,7 @@[m [mprotected:[m
 public:[m
 	virtual ~VisibleWearable();[m
 [m
[31m-	VisibleWearable(const VisibleWearable& other) : PickableObject(other), Wearable(other), renderer(other.renderer), tag(other.tag) {}[m
[32m+[m	[32mVisibleWearable(const VisibleWearable& other) : Wearable(other), renderer(other.renderer), tag(other.tag) {}[m
 [m
 	virtual VisibleWearable* clone() const {[m
 		return new VisibleWearable(*this);[m
[1mdiff --git a/Source/Objects/Wearable.cpp b/Source/Objects/Wearable.cpp[m
[1mindex b92f062..4389483 100644[m
[1m--- a/Source/Objects/Wearable.cpp[m
[1m+++ b/Source/Objects/Wearable.cpp[m
[36m@@ -5,5 +5,9 @@[m [mWearable::~Wearable()[m
 [m
 }[m
  [m
[32m+[m[32mWearable::Wearable(string identifier, int posx, int posy, string tx, RenderContext& renderer) :[m
[32m+[m	[32mPickableObject(identifier, posx, posy, tx, renderer, true)[m
[32m+[m[32m{[m
 [m
[32m+[m[32m}[m
 [m
[1mdiff --git a/Source/Objects/Wearable.h b/Source/Objects/Wearable.h[m
[1mindex 2125175..861367e 100644[m
[1m--- a/Source/Objects/Wearable.h[m
[1m+++ b/Source/Objects/Wearable.h[m
[36m@@ -1,36 +1,45 @@[m
 #ifndef WEARABLE_H[m
 #define WEARABLE_H[m
 [m
[32m+[m[32m#include "PickableObject.h"[m
 #include "../Characters/Player.h"[m
 [m
 /// <summary>[m
 /// An Object is an Entity that can be found in a Room, for the Player to interact with, in a Chest (which is an Object in and of itself), for the Player to collect, or in a Player's inventory, for the Player to use.[m
 /// </summary>[m
[31m-class Wearable[m
[32m+[m[32mclass Wearable : public PickableObject[m
 {[m
 protected:[m
 [m
 public:[m
 	virtual ~Wearable();[m
 [m
[32m+[m	[32mWearable(const Wearable& other) : PickableObject(other) {}[m
[32m+[m
[32m+[m	[32mvirtual Wearable* clone() const {[m
[32m+[m		[32mreturn new Wearable(*this);[m
[32m+[m	[32m}[m
[32m+[m
[32m+[m	[32mWearable(string identifier, int posx, int posy, string tx, RenderContext& renderer);[m
[32m+[m
 	/// <summary>[m
 	/// Called when the user chooses to wear the object. See the remove function to undo the equip action below.[m
 	/// </summary>[m
 	/// <param name="p"></param>[m
[31m-	virtual void equip(Player* p)const = 0;[m
[32m+[m	[32mvirtual void equip(Player* p)const {}[m
 [m
 	/// <summary>[m
 	/// Called when the player puts off the object.[m
 	/// </summary>[m
 	/// <param name="p"></param>[m
[31m-	virtual void remove(Player* p)const = 0;[m
[32m+[m	[32mvirtual void remove(Player* p)const {}[m
 [m
 	/// <summary>[m
 	/// Returns a value indicating the status of the object.[m
 	/// </summary>[m
 	/// <param name="p"></param>[m
 	/// <returns></returns>[m
[31m-	virtual bool isWorn(Player* p)const = 0;[m
[32m+[m	[32mvirtual bool isWorn(Player* p)const { return false; }[m
 };[m
 [m
 #endif[m
[1mdiff --git a/Source/main.cpp b/Source/main.cpp[m
[1mindex a61b22d..f0832fa 100644[m
[1m--- a/Source/main.cpp[m
[1m+++ b/Source/main.cpp[m
[36m@@ -37,7 +37,7 @@[m [mint main(int argc, char** argv)[m
 int playDoarm(GAME* game)[m
 {[m
 	RenderContext& renderer = *(game->renderer);[m
[31m-	Player* me = new Player(renderer);[m
[32m+[m	[32mPlayer* me = new Player(renderer, SAVES_CURRENT);[m
 [m
 	game->player = me;[m
 	game->currentMap = new MainMenu(*me, game);[m
