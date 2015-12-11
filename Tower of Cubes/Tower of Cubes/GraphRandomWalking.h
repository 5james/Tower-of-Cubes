#pragma once
#include "Graph.h"


class GraphRandomWalking : public Graph
{
private:
	bool cubeIsNotVisited(std::vector<int>& cubesVisited, int id);
	void RandomWalking(Node* actual, std::vector<int> &cubesVisited);
public:
	void solve();


};

