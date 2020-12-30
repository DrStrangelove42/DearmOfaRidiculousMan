#include "Story.h"

void Story::fromFile(string path)
{
	ifstream file(path);
	string line;

	while (getline(file, line))
	{
		string type = getLineType(line);

		if (type == "PART")
		{

		}
		else if (type == "OBJ")
		{

		}
		else if (type == "MOB")
		{

		}
		else if (type == "NPC")
		{

		}
		else
		{

		}
	}
}

string Story::getLineType(string& line)
{
	return NextToken(line);
}



Story::Story(string name) : curPart(0)
{
	fromFile(STORYFILES_LOCATION + name + STORYFILES_EXT);
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

void Story::Part::branch(int i)
{
	if (curStep->choices.size() > i)
		curStep = curStep->choices[i];
}
