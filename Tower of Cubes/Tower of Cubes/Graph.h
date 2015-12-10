#pragma once

#include <vector>
#include "Node.h"

class Graph
{
protected:
	std::vector <Node> nodes;

	void generateColoursCube(std::vector<int> &colors);
	void addCubeToNodes(int id);
	void addCubeNeighbourhood();
	void addColourNeighbourhood();
public:
	Graph();
	~Graph();
	void generateNodes();
	void showNodes();
	virtual void solve() = 0;
};

