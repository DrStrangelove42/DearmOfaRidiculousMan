#include "Story.h"
#include "../Maps/Map.h"

void Story::fromFile(string path, GAME* game)
{
	ifstream file(path);
	string line;
	int id = 0xffff;
	RenderContext& r = *(game->renderer);
	Player& p = *(game->player);

	string firstPart = "";
	//TODO set start map
	string worldName = "MainMap";
	game->worldName = worldName;
	*(game->currentMapId) = -1;
	game->currentMap = new Map(worldName, *(game->player), r, game->currentMapId);
	string curPartName = "";
	Part* parsingPart = new Part();
	while (getline(file, line))
	{
		string type = EatToken(line);
		if (type == "REM") continue;
		if (type == "PART")
		{
			if (curPartName.empty())
				//first part
				firstPart = line;
			else
				//flush previous part
				parts[curPartName] = parsingPart;
			//PART <name>
			curPartName = line;
			parsingPart = new Part();
		}
		else
		{
			int x, y;
			x = stoi(EatToken(line));
			y = stoi(EatToken(line));

			if (type == "OBJ")
			{
				Object* obj = Map::parseObject(line, r, &id, x, y);
				parsingPart->scenario.push_back(new Step(
					[obj](GAME* game)
					{
						game->currentMap->getCurrentRoomObject().addObject(obj);
					}
				));
			}
			else if (type == "MOB")
			{
				//Monsters parsed from here will need to be teleported according to the current 
				//room obviously (see Room::addMonster).           vvvv
				Monster* mob = Map::parseMonster(line, r, x, y, p, NULL);
				parsingPart->scenario.push_back(new Step(
					[mob](GAME* game)
					{
						game->currentMap->getCurrentRoomObject().addMonster(mob);
					}
				));
			}
			else if (type == "NPC")
			{
				//NPC x y textureID,name,speech,choice1,partIndex1,...
				/*Choice is the text of the choice, followed the index of a part in the following comma-separated token*/
				string npc_txID = EatToken(line, ',');
				string npc_name = EatToken(line, ',');
				string npc_speech = EatToken(line, ',');
				//TODO : maybe blocking NPCs ?                              -->   vvvv
				NPC* npc = new NPC(npc_name, npc_speech, x, y, npc_txID, r, NULL, true);
				// The map will be set when the NPC is updated in it.       ^^^^
				while (!line.empty())
				{
					string npc_curChoice = EatToken(line, ',');

					string partIdx = EatToken(line, ',');
					npc->addChoice(npc_curChoice, r, [this, partIdx](int choiceId)
						{
							this->changePart(partIdx);
						}
					);

				}

				parsingPart->scenario.push_back(new Step(
					[npc](GAME* game)
					{
						game->currentMap->getCurrentRoomObject().addObject(npc);
					}
				));
			}
			else
			{
				if (DEBUG_MODE)
					cout << "Story parse error : unknown action type " << type << endl;
			}
		}
	}
	if (!curPartName.empty())
	{
		parts[curPartName] = parsingPart;
	}
	curPart = parts[firstPart];

	file.close();
}



Story::Story(string name, GAME* game)
{
	fromFile(STORYFILES_LOCATION + name + STORYFILES_EXT, game);
}

Story::~Story()
{
	for (auto& p : parts)
	{
		delete p.second;
	}
	parts.clear();
}

void Story::tick(int time, GAME* game)
{
	if (curPart->done) return;

	Step* step = getCurrentStep();

	if (!step->done)
	{
		step->action(game);
		step->done = true; //we do not go backward
	}

	curPart->nextStep();
}

void Story::onKeyDown(GAME* game)
{

}

void Story::branch(int index)
{
	curPart->branch(index);
}

void Story::changePart(string index)
{
	if (parts.find(index) != parts.end())
		curPart = parts[index];
}

Story::Step* Story::getCurrentStep()
{
	return curPart->scenario[curPart->curStep];
}

Story::Part::Part() : curStep(0), done(false)
{

}

void Story::Part::branch(int i)
{
	if (scenario.size() > i)
		curStep = i;
}

void Story::Part::nextStep()
{
	if (scenario.size() > curStep + 1)
	{
		curStep++;
	}
	else
		done = true;
}


Story::Step::Step(function<void(GAME*)> action) : action(action), done(false)
{

}
