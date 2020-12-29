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
	return NextToken(line, ' ');
}



Story::Story(string name)
{
	fromFile(STORYFILES_LOCATION + name + STORYFILES_EXT);
}

void Story::tick(int time, GAME* game)
{

}

void Story::onKeyDown(GAME* game)
{

}
