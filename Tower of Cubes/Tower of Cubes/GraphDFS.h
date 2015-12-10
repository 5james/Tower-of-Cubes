#pragma once
#include "Graph.h"
#include <stack>

class GraphDFS : public Graph
{
private:
	void DFS(Node* actual, std::vector<int> &cubesVisited, std::vector<int> &maxTower, bool inside);
public:
	void solve();


};

