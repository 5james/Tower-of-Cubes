// Wieza N szescianow
// autor: Jakub Guzek
// ver 0.1

#pragma once


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
	Graph(Graph &g);
	Graph(int amountOfCubes, int coloursx, int maxWeightx);
	Graph(char *name);
	~Graph();
	void generateNodes();
	void loadNodes(char *name);
	void showNodes();
	std::vector<Node>* getNodes();
	int getCubes();
	int getColours();
	int getMaxWeight();

	virtual void solve() = 0;
};

