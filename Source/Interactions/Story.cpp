#include "Story.h"
#include "../Maps/Map.h"
#include "../Maps/Banner.h"

void Story::fromFile(string path, GAME* game)
{
	ifstream file(path);
	string line;
	int id = 0xffff;
	RenderContext& r = *(game->renderer);
	Player& p = *(game->player);

	string firstPart = "";
	bool foundMap = false;
	string curPartName = "";
	Part* parsingPart = new Part();
	int curRoom = 0;

	while (getline(file, line))
	{
		string type = EatTokenEx(line);
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
		else if (type == "MAP")
		{
			string world_name = EatTokenEx(line, ',');
			string map_idx = EatTokenEx(line, ',');
			string room_idx = EatTokenEx(line, ',');
			int map_idx_toi = stoi(map_idx);
			int room_idx_toi = stoi(room_idx);
			
			curRoom = room_idx_toi;
			
			if (!foundMap)//No start map
			{
				int startMap = map_idx_toi;
				foundMap = true;
				changeMap(game, world_name, startMap, room_idx_toi);
			}
			else {
				parsingPart->scenario.push_back(new Step(
					[world_name, map_idx_toi, room_idx_toi](GAME* game)
					{
						int startMap = map_idx_toi;
						changeMap(game, world_name, startMap, room_idx_toi);
					}
				));
			}
		}
		else if (type == "ROOM")
		{
			curRoom = stoi(line);
		}
		else if (type == "BANNER")
		{
			string text = EatTokenEx(line, ',');
			string delay = EatTokenEx(line, ',');
			int ddelay = stoi(delay);
			string world_name = EatTokenEx(line, ',');
			string map_idx = EatTokenEx(line, ',');
			string room_idx = EatTokenEx(line, ',');
			int map_idx_toi = stoi(map_idx);
			int room_idx_toi = stoi(room_idx);


			parsingPart->scenario.push_back(new Step(
				[text, ddelay,world_name, map_idx_toi, room_idx_toi](GAME* game)
				{
					string id = "banners/" + text;
					if (isLoaded(id, 0))
						changeMap(game, id, 0, 0);
					else
					{
						game->worldName = id;
						*game->currentMapId = 0;
						game->currentMap = new Banner(*(game->player),game,text, ddelay, world_name, map_idx_toi, room_idx_toi);
					}
				}
			));

		}
		else
		{
			int x, y;
			x = stoi(EatTokenEx(line));
			y = stoi(EatTokenEx(line));

			if (type == "OBJ")
			{
				Object* obj = Map::parseObject(line, r, &id, x, y);
				parsingPart->scenario.push_back(new Step(
					[obj,curRoom](GAME* game)
					{
						game->currentMap->getRooms()[curRoom]->addObject(obj);
					}
				));
			}
			else if (type == "MOB")
			{
				//Monsters parsed from here will need to be teleported according to the current 
				//room obviously (see Room::addMonster).           vvvv
				Monster* mob = Map::parseMonster(line, r, x, y, p, NULL);
				parsingPart->scenario.push_back(new Step(
					[mob, curRoom](GAME* game)
					{
						game->currentMap->getRooms()[curRoom]->addMonster(mob);
					}
				));
			}
			else if (type == "NPC")
			{
				//NPC x y textureID,name,speech,choice1,partIndex1,...
				/*Choice is the text of the choice, followed the index of a part in the following comma-separated token*/
				string npc_txID = EatTokenEx(line, ',');
				string npc_name = EatTokenEx(line, ',');
				string npc_speech = EatTokenEx(line, ',');
				//TODO : maybe blocking NPCs ?                              -->   vvvv
				NPC* npc = new NPC(npc_name, npc_name, npc_speech, x, y, npc_txID, r, NULL, true);
				// The map will be set when the NPC is updated in it.       ^^^^
				while (!line.empty())
				{
					string npc_curChoice = EatTokenEx(line, ',');

					string partIdx = EatTokenEx(line, ',');
					npc->addChoice(npc_curChoice, r, [this, partIdx](int choiceId)
						{
							this->changePart(partIdx);
						}
					);

				}

				parsingPart->scenario.push_back(new Step(
					[npc, curRoom](GAME* game)
					{
						game->currentMap->getRooms()[curRoom]->addObject(npc);
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
		step->done = true; //we do not go backwards
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
