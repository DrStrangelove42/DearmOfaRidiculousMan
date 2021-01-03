#include "Story.h"
#include "../Maps/Map.h"

void Story::fromFile(string path, GAME* game)
{
	ifstream file(path);
	string line;
	int id = 0xffff;
	RenderContext r = *(game->renderer);
	Player p = *(game->player);
	 
	string curPartName = "";
	Part* curPart = new Part();
	while (getline(file, line))
	{
		string type = EatToken(line);

		if (type == "PART")
		{
			//flush previous part
			parts[curPartName] = curPart;
			//PART <name>
			curPartName = line;
			curPart = new Part();
		}
		else
		{
			int x, y;
			x = stoi(EatToken(line));
			y = stoi(EatToken(line));

			if (type == "OBJ")
			{
				Object* obj = Map::parseObject(line, r, &id, x, y);
				curPart->scenario.push_back(new Step(
					[obj](GAME* game) {
						game->currentMap->getCurrentRoomObject().addObject(obj);
					}
				));
			}
			else if (type == "MOB")
			{
				//Monsters parsed from here will need to be teleported according to the current 
				//room obviously (see Room::addMonster).           vvvv
				Monster* mob = Map::parseMonster(line, r, x, y, p, NULL);
				curPart->scenario.push_back(new Step(
					[mob](GAME* game) {
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
				//TODO : maybe blocking NPCs ?                        -->   vvvv
				NPC* npc = new NPC(npc_name, npc_speech, x, y, npc_txID, r, true);
				while (!line.empty())
				{
					string npc_curChoice = EatToken(line, ',');

					string partIdx = EatToken(line, ',');
					npc->addChoice(npc_curChoice, r, [p, partIdx](int choiceId) {p.getStory().changePart(partIdx); });

				}
			}
			else
			{
				if (DEBUG_MODE)
					cout << "Story parse error : unknown action type " << type << endl;
			}
		}
	}
}



Story::Story(string name, GAME* game) : curPart(0)
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

Story::Part::Part() : curStep(0)
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
