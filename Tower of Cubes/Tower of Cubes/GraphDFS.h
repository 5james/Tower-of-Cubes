#pragma once
#include "Graph.h"
#include "GraphBFSTree.h"
#include <vector>


class GraphDFS : public Graph
{
private:
	bool cubeIsNotVisited(std::vector<std::pair<int, Node*> >& cubesVisited, int id);
	void DFS(Node* actual, std::vector<std::pair<int, Node*> > &cubesVisited, std::vector<std::pair<int, Node*> > &maxTower, bool inside, int nested);
public:
	GraphDFS(int amountOfCubes, int coloursx, int maxWeightx);
	GraphDFS(GraphBFSTree &g);
	~GraphDFS();
	void solve();


};

