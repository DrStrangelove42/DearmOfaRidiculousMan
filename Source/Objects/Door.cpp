#include "Door.h"
#include "../Characters/Player.h"
Door::~Door()
{

}

Door::Door(string keyId, string openOrientation, string closedOrientation, string identifier, int posx, int posy, RenderContext& renderer) : keyId(keyId), openOrientation(openOrientation), closedOrientation(closedOrientation), Object(identifier, posx, posy, "door" + closedOrientation, renderer, false)
{

}

Door::Door(string headerline, int posx, int posy, RenderContext& renderer) : Object("", posx, posy, "empty", renderer, false)
{
	auto iss = istringstream{ headerline };
	string str = "";
	/*Tokenisation, more reliable*/
	vector<string> tokens;
	while (iss >> str)
	{
		tokens.push_back(str);
	}
	/*
	Recall the structure of Door info :
	0 -> !<ID>
	1 -> KeyId
	2 -> ClosedOrientation
	3 -> OpenOrientation
	4 -> 'c' if closed, 'o' if open (optional, 'c' by default)
	*/

	string id = tokens[0], keyId = tokens[1], closedOr = tokens[2], openOr = tokens[3];
	*this = Door(keyId, openOr, closedOr, id, posx, posy, renderer);
	if (tokens.size() > 4 && tokens[4] == "o")
	{
		traversable = true;
		texture = "door" + openOrientation;
		updateTexture(renderer);		
	}
}

bool Door::updateObject(GAME* game)
{
	if (traversable || abs(x - game->player->getX()) + abs(y - game->player->getY()) > 1)
	{
		return false;
	}
	if (game->player->hasObject("k" + keyId))
	{
		traversable = true;
		texture = "door" + openOrientation;
		updateTexture(*(game->renderer));
	}

	return false;
}

string Door::objectToString()
{
	return id + " " + keyId + " " + closedOrientation + " " + openOrientation + (traversable ? "o" : "");
}
