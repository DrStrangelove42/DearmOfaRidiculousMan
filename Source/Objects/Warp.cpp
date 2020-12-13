#include "Warp.h"
#include "../Maps/Map.h"
#include "../Maps/MainMenu.h"

Warp::~Warp()
{

}

Warp::Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, RenderContext& renderer, int delay) :
	Object(identifier, posx, posy, "empty", renderer, true), destMap(destMap), destRoom(destRoom), destX(destX), destY(destY), delay(delay), destWorld("")
{

}

Warp::Warp(int destMap, int destRoom, int destX, int destY, int posx, int posy, string identifier, RenderContext& renderer, int delay, string destWorld) :
	Object(identifier, posx, posy, "empty", renderer, true), destMap(destMap), destRoom(destRoom), destX(destX), destY(destY), delay(delay), destWorld(destWorld)
{

}

Warp::Warp(string information, int* uniqueId, int posx, int posy, RenderContext& renderer) :
	Object(information.substr(0, 2) + to_string((*uniqueId)++), posx, posy, "empty", renderer, true), delay(0), destWorld("")
{
	size_t a;
	auto iss = istringstream{ information };
	string str = "";
	/*Tokenisation, more reliable*/
	vector<string> tokens;
	while (iss >> str)
	{
		tokens.push_back(str);
	}
	/*
	Recall the structure of Warp info :
	0 -> !<ID>
	1 -> MapID
	2 -> RoomID
	3 -> destX
	4 -> destY
	5 -> [delay]	| [X
	6 ->			|  <dest world>]
	*/

	destMap = stoi(tokens[1]);
	destRoom = stoi(tokens[2]);
	destX = stoi(tokens[3]);
	destY = stoi(tokens[4]);
	int last = 5;
	if (tokens.size() > last) {
		try
		{
			delay = stoi(tokens[last]);
			last++;
		}
		catch (...)/*Not a number*/
		{
		}
		if (tokens.size() > last && tokens[last] == "X")
		{
			last++;
			/*External warp*/
			if (tokens.size() > last)
			{
				destWorld = tokens[last];
			}
			else
			{
				cout << "Ill-formed external warp : world empty." << endl;
			}
		}
	}
}

void Warp::updateObject(GAME* game)
{
	if (delay > 0)
	{
		delay--;
		return;
	}
	if (x != game->player->getX() || y != game->player->getY())
	{
		return;
	}

	RenderContext& renderer = *(game->renderer);
	game->player->teleport(destX, destY);
	game->currentMap->currentRoom = destRoom;
	if (destWorld.empty())
	{
		if (destMap == -1)
		{
			*(game->currentMapId) = -1;
			game->currentMap = new MainMenu(*(game->player), game);
			game->worldName = "Main menu";
			return;
		}
		if (destMap != *(game->currentMapId))
		{
			*(game->currentMapId) = destMap;
			game->currentMap = new Map(game->worldName, *(game->player), renderer, game->currentMapId, destRoom);
		}
		else
			game->currentMap->getRooms()[destRoom]->setDiscovered(true);
	}
	else
	{
		game->worldName = destWorld;
		*(game->currentMapId) = -1;
		game->currentMap = new Map(destWorld, *(game->player), *(game->renderer), game->currentMapId);
	}
}
