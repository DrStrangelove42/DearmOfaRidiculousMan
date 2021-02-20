#include "utils.h"
#include <string.h>
using namespace std;

/// <summary>
/// This file is for helpers functions. All functions in this file (and only these
/// ones) begin with a capital letter.
/// </summary>
/// <returns></returns>
int InitUtils()
{
	srand(static_cast<unsigned int>(time(NULL)));

	LoadTextFromLanguage(LANGUAGE);

	return 0;
}

/// <summary>
/// Returns a pseudo-random number in [0, max[.
/// </summary>
/// <param name="max"></param>
/// <returns></returns>
int GetRandom(int max)
{
	return rand() % max;
}

/// <summary>
/// 
/// </summary>
/// <param name="err"></param>
/// <returns></returns>
int DumpError(string err)
{
	cout << "Error : " << err << "\nInternal error: " << RenderContext::RenderErrorDetails() << endl;
	return EXIT_FAILURE;
}

/// <summary>
/// Get the number of elapsed milliseconds since the lauch of the game.
/// </summary>
/// <returns></returns>
int GetTime()
{
	using namespace std::chrono;
	static high_resolution_clock::time_point referenceTime = high_resolution_clock::now();
	high_resolution_clock::time_point n = high_resolution_clock::now();
	duration<double, milli> time_span = n - referenceTime;
	return (int)time_span.count();
}

string NextToken(string& line, char sep)
{
	return line.substr(0, line.find_first_of(sep));
}

string EatToken(string& line, char sep)
{
	size_t i = line.find_first_of(sep);
	string newLine = line;
	if (i != line.npos)
	{
		line = line.substr(i + 1);
		return newLine.substr(0, i);
	}
	else
	{
		line = "";
		return newLine;
	}
}

string EatTokenEx(string& line, char sep)
{
	//Invariant : line commence par un jeton, puis son séparateur (pas de séparateur au début).
	size_t start = line.find_first_not_of(' '); //Espaces au début
	if (start == line.npos) //Rien trouvé
	{
		line = "";
		return "";
	}
	line = line.substr(start);
	string nline = line;
	size_t sepI = line.find_first_of(sep); //le séparateur
	if (sepI == line.npos) //Pas de séparateur
	{
		sepI = line.size();
		line = "";
	}
	else
	{
		line = line.substr(sepI + 1);
	}
	//Espaces après le jeton
	nline = nline.substr(0, sepI);
	size_t end = nline.find_last_not_of(' ') + 1;
	nline = nline.substr(0, end);
	return nline;
}

map<string, string> loadedStrings;

string GetText(string id)
{
	if (loadedStrings.find(id) == loadedStrings.end())
		return id;
	else
		return loadedStrings[id];
}

void LoadTextFromLanguage(string& langCode)
{
	struct stat dummy;
	string line;
	string fname = LANG_LOCATION + langCode + LANGFILES_EXT;
	if (stat(fname.c_str(), &dummy) != 0)
	{
		 
		cout << fname << " doesn't exist..." << endl;
		return;
	}

	ifstream stream(fname);
	string curID = "";
	string curValue = "";
	while (getline(stream, line))
	{
		if (line[0] == '#')
		{
			if (!curValue.empty())
			{
				loadedStrings[curID] = curValue;
				curValue = "";
			}
			curID = line.substr(1);
		}
		else
		{
			if (curValue.empty())
				curValue += line;
			else
				curValue += '\n' + line;
		}
	}

	if (!curValue.empty())
		loadedStrings[curID] = curValue;
}

bool RectContains(Rect* r, int x, int y)
{
	return r->x <= x && r->y <= y && x - r->x <= r->w && y - r->y <= r->h;
}