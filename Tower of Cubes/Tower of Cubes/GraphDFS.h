#pragma once
#include "Graph.h"


class GraphDFS : public Graph
{
private:
	bool cubeIsNotVisited(std::vector<int>& cubesVisited, int id);
	void DFS(Node* actual, std::vector<int> &cubesVisited, std::vector<int> &maxTower, bool inside, int nested);
public:
	void solve();


};

