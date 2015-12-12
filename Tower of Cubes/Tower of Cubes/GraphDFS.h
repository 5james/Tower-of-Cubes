#pragma once
#include "Graph.h"


class GraphDFS : public Graph
{
private:
	bool cubeIsNotVisited(std::vector<std::pair<int, Node*> >& cubesVisited, int id);
	void DFS(Node* actual, std::vector<std::pair<int, Node*> > &cubesVisited, std::vector<std::pair<int, Node*> > &maxTower, bool inside, int nested);
public:
	void solve();


};

