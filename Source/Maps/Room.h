#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "../Base/Entity.h"
#include "../Base/game.h"
#include "../Base/utils.h"
#include "../Blocks/FloorBlock.h"
#include "../Blocks/Block.h"
#include "../Objects/Object.h"
#include <unordered_map>
#include <list>
#include "../Characters/Monster.h"

using namespace std;

class Map;

/// <summary>
/// A Room is a structure composed of <see cref="Block">Blocks</see>, arranged in a grid, in which the Player can move.
/// </summary>
class Room : public Entity
{
protected:
	/// <summary>
	/// Width of the Room, in blocks<see cref="Block">Blocks</see>.
	/// </summary>
	int w;

	/// <summary>
	/// Height of the Room, in blocks<see cref="Block">Blocks</see>.
	/// </summary>
	int h;

	/// <summary>
	/// X coordinate of the absolute location of the first Block (top-left corner, blocks[0][0]) of this Room in the Map, in <see cref="Block">Blocks</see>.
	/// </summary>
	int x;

	/// <summary>
	/// Y coordinate of the absolute location of the first Block (top-left corner, blocks[0][0]) of this Room in the Map, in <see cref="Block">Blocks</see>.
	/// </summary>
	int y;

	/// <summary>
	/// A reference to the Player.
	/// </summary>
	Player& player;

	/// <summary>
	/// A matrix of size w times h of references to <see cref="Block">Blocks</see>, which are the basic compound of a Room.
	/// </summary>
	Block*** blocks;

	/// <summary>
	/// A boolean indicating whether the Room has already been visited by the Player. We will only show on screen the <see cref="Room">Rooms</see> that have been discovered.
	/// </summary>
	bool discovered;

	/// <summary>
	/// The unordered_map of <see cref="Object">Objects</see> in the Room.
	/// </summary>
	unordered_map <string, Object*> objects;

	/// <summary>
	/// The list of <see cref="Monster">Monsters</see> in the Room.
	/// </summary>
	list<Monster*> monsters;

	/// <summary>
	/// A list of <see cref="Monster">Monsters</see> that need deleting from the Room.
	/// </summary>
	list<Monster*> pendingToRemove;

	/// <summary>
	/// Time at which the Room was last <see cref="Room::cleanMonsters">cleaned</see>, in ticks.
	/// </summary>
	int lastCleaned = 0;

	/// <summary>
	/// Minimal time between each <see cref="Room::cleanMonsters">cleaning</see> of the Room.
	/// </summary>
	int cleanDelay = 10000;

	/// <summary>
	/// A boolean to be used when we want the Room to stop updating its <see cref="Object">Objects</see>, notably when the Player <see cref="Warp">Warps</see>.
	/// </summary>
	bool breakObjectUpdateLoop;
public:
	/// <summary>
	/// Room constructor.
	/// </summary>
	Room(int width, int height, int absx, int absy, Player& p, RenderContext& renderer);

	/// <summary>
	/// Tells us whether a certain Block is <see cref="Block::traversable">traversable</see> or not.
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	bool isTraversable(int, int);

	/// <summary>
	/// Adds a Monster to the Room.
	/// </summary>
	/// <param name="m"></param>
	void addMonster(Monster* m);

	/// <summary>
	/// Removes the Monster from the Room.
	/// </summary>
	/// <param name="m"></param>
	void removeMonster(Monster* m);

	/// <summary>
	/// Removes the Object having <see cref="Object::id">identifier</see> id from the Room.
	/// </summary>
	/// <param name="id"></param>
	void removeObject(string id);

	/// <summary>
	/// Destructor.
	/// </summary>
	virtual ~Room();

	/// <summary>
	/// Adds an Object to the Room.
	/// </summary>
	/// <param name="object"></param>
	void addObject(Object* object);

	/// <summary>
	/// Adds an Object near the specified position in the Room, but not on this precise position.
	/// </summary>
	/// <param name="object"></param>
	void addObject(Object* object, int x, int y);

	/// <summary>
	/// Tells the Room that it must stop updating its <see cref="Object">Objects</see>, notably when a Warp is used.
	/// </summary>
	void stopScanningObjects();

	/// <summary>
	/// Attempts to change the Entity's position, by first seeing of the Block is <see cref="Block::traversable">traversable</see>.
	/// </summary>
	/// <param name="e"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void tryTeleportAt(MovingEntity& e, int x, int y);

	/// <summary>
	/// Updates all <see cref="Object">Objects</see> in the Room accordingly.
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	void tick(int time, GAME* game);

	/// <summary>
	/// Updates all <see cref="Monster">Monsters</see> in the Room accordingly.
	/// </summary>
	/// <param name="time"></param>
	/// <param name="game"></param>
	void updateAllMonsters(int time, GAME* game);

	/// <summary>
	/// <see cref="RenderContext">Rendering</see> method, enabling the <see cref="RenderContext::renderer">renderer</see> to take the offset (in <see cref="Block">blocks</see>) into account.
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="offsetX"></param>
	/// <param name="offsetY"></param>
	virtual void render(RenderContext& renderer, int offsetX = 0, int offsetY = 0)const;

	/// <summary>
	/// Changes a Block in the Room, according to its location
	/// </summary>
	/// <param name="newBlock"></param>
	void replaceBlock(Block* newBlock);

	/// <summary>
	/// When a <see cref="GAME::key">key</see> is pushed on the keyboard.
	/// </summary>
	/// <param name="ea"></param>
	virtual void onKeyDown(GAME* game);

	/// <summary>
	/// Returns the Block where the Player is situated.
	/// </summary>
	/// <returns></returns>
	Block* getCurrentBlock();

	/* Accessors */
	int getW()const;
	int getH()const;
	int getX()const;
	int getY()const;
	Block*** getBlocks();
	list<Monster*>& getMonsters();
	unordered_map <string, Object*>& getObjects();

	/* Setter */
	void setDiscovered(bool b);

	/// <summary>
	/// Removes dead <see cref="Monster">monsters</see>.
	/// </summary>
	void cleanMonsters();

	/// <summary>
	/// Adds the Warp information to every IntelligentMonster in the Room.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="destRoom"></param>
	/// <param name="destX"></param>
	/// <param name="destY"></param>
	/// <param name="playerJustLeft"></param>
	void sendMonstersToWarp(int x, int y, int destRoom, int destX, int destY, bool playerJustLeft);

	/// <summary>
	/// Empties the <see cref="IntelligentMonster">IntelligentMonsters</see> in the Room of their <see cref="IntelligentMonster::warpInfo">warpInfo</see>: this is for when the <see cref="IntelligentMonster">IntelligentMonsters</see> are in the same Room as the Player and so they no longer need to go towards a Warp. The information needs to be cleaned to prepare for the next time that the Player <see cref="Warp">Warps</see>.
	/// </summary>
	void cleanMonsterWarpInfo();

	/// <summary>
	/// Informs the Room that the Monster needs to be removed next time the Room is <see cref="Room::cleanMonsters">cleaned</see>.
	/// </summary>
	/// <param name="m"></param>
	void addMonsterToRemove(Monster* m);

	/// <summary>
	/// Returns the string that encodes the Object having the given identifier in the Room.
	/// If the object is not in the room, returns an empty string ("").
	/// </summary>
	/// <param name="id"></param>
	string getObjectString(string id);
};


#endif
