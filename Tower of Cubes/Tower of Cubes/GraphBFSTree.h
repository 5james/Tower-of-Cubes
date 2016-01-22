// Wieza N szescianow
// autor: Jakub Guzek
// ver 0.1

//Low eficiency when low amount of colours in comparison with number of cubes

#pragma once
#include "Graph.h"
#include <vector>


class GraphBFSTree : public Graph
{
private:

	class SimpleNodesTree
	{
	public:
		SimpleNodesTree* parent;
		int id;
		int bottomColor;
		int depth;
		std::vector<SimpleNodesTree*> child;
		bool operator< (SimpleNodesTree& q)
		{
			if (id < q.id)
				return true;
			return false;
		}
		bool operator== (SimpleNodesTree& q)
		{
			if (id == q.id)
				return true;
			return false;
		}
	};


	//void colorOnBottom(SimpleNodesTree* &current);
	std::vector<std::pair<int, int>> allNeighboursOfIdWithColour(int id, int colour);
	bool checkOppositeWallsColour(SimpleNodesTree* toCheck);
	bool isIdUnique(int id, SimpleNodesTree* current);


public:
	GraphBFSTree(int amountOfCubes, int coloursx, int maxWeightx);
	GraphBFSTree(Graph& g);
	GraphBFSTree(char *name);
	~GraphBFSTree();
	void solve();	
};

