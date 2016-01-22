#pragma once

#include "declarations.h"
#include <vector>
#include "Node.h"

class Graph
{
protected:
	std::vector <Node> nodes;
	int cubes, colours, maxWeight;

	void generateColoursCube(std::vector<int> &colors);
	void addCubeToNodes(int id);
	void addCubeNeighbourhood();
	void addColourNeighbourhood();
public:
	Graph();
	Graph(int amountOfCubes, int coloursx, int maxWeightx);
	~Graph();
	void generateNodes();
	void showNodes();
	virtual void solve() = 0;
};

