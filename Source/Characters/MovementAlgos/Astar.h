#ifndef ASTAR_H
#define ASTAR_H


/// <summary>
/// In this file we inplement the Astar algorithm for the monster movement
/// </summary>

using namespace std;
class AStar
	{
	public:
		AStar();
		vector<Map> findPath(const Map& startPos, const Map& targetPos, HeuristicFunction heuristicFunc, int weight = 1);
		void loadMap(const tring& fileName);
		void setDiagonalMovement(bool enable);

	private:
		vector<Map> buildPath() const;
		bool isValid(const Map& pos) const;
		bool isBlocked(int index) const;
		int convertTo1D(const Map& pos) const;

		int m_weight;
		int m_size;
		uint m_nrOfDirections;
		Map m_dimensions;
		Map m_startPos;
		Map m_targetPos;
		priority_queue<Node> m_openList;
		vector<bool> m_closedList;
		vector<Node> m_cameFrom;
		vector<int> m_grid;
		vector<Map> m_directions;
		HeuristicFunction m_heuristic;
    }






#endif