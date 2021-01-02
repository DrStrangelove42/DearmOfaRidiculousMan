#include "Story.h"
#include "../Maps/Map.h"

void Story::fromFile(string path, GAME* game)
{
	ifstream file(path);
	string line;
	int id = 0xffff;
	RenderContext r = *(game->renderer);
	Player p = *(game->player);
	Room dummyRoom = game->currentMap->getCurrentRoomObject();

	Part* curPart = new Part();
	while (getline(file, line))
	{
		string type = EatToken(line);
		int x, y;
		x = stoi(EatToken(line));
		y = stoi(EatToken(line));
		if (type == "PART")
		{
			parts.push_back(curPart);
			curPart = new Part();
		}
		else if (type == "OBJ")
		{
			Map::parseObject(line, r, &id, x, y);
		}
		else if (type == "MOB")
		{
			//Monsters parsed from here will need to be teleported according to the current room obviously.
			Map::parseMonster(line, r, x, y, p, dummyRoom);
		}
		else if (type == "NPC")
		{

		}
		else
		{

		}
	}
}



Story::Story(string name, GAME* game) : curPart(0)
{
	fromFile(STORYFILES_LOCATION + name + STORYFILES_EXT, game);
}

Story::~Story()
{
	for (Part* p : parts)
	{
		delete p;
	}
	parts.clear();
}

void Story::tick(int time, GAME* game)
{

}

void Story::onKeyDown(GAME* game)
{

}

void Story::branch(int index)
{
	parts[curPart]->branch(index);
}

void Story::changePart(int index)
{
	if (parts.size() > index)
		curPart = index;
}

Story::Part::Part()
{
}

void Story::Part::branch(int i)
{
	if (curStep->choices.size() > i)
		curStep = curStep->choices[i];
}
