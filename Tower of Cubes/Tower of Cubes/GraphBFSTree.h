#pragma once
#include "Graph.h"

class GraphBFSTree : public Graph
{
private:

public:
	std::vector<int> allNeighboursOfId(int id);

	void solve();

	class SimpleNodesTree
	{
	public:
		SimpleNodesTree* parent;
		int id;
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
private:
	bool isIdUnique(int id, SimpleNodesTree* current);
};

