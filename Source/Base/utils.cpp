#include "utils.h"

using namespace std;
 
/// <summary>
/// This file is for helpers functions. All functions in this file (and only these
/// ones) begin with a capital letter.
/// </summary>
/// <returns></returns>
int InitUtils()
{
	srand(static_cast<unsigned int>(time(NULL)));

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