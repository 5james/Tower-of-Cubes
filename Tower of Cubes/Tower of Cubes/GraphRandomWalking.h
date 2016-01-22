#pragma once

#include "Graph.h"


class GraphRandomWalking : public Graph
{
private:
	bool cubeIsNotVisited(std::vector<std::pair<int, Node*> >& cubesVisited, int id);
	void RandomWalking(Node* actual, std::vector<std::pair<int, Node*> > &cubesVisited);
public:
	GraphRandomWalking(int amountOfCubes, int coloursx, int maxWeightx);
	GraphRandomWalking(Graph &g);
	GraphRandomWalking();
	~GraphRandomWalking();
	void solve();


};

