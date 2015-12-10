#include <iostream>
#include <time.h>
#include "Graph.h"
#include "GraphBFSTree.h"

int main()
{
	srand((unsigned)time((time_t)NULL));
	//Graph g;
	//g.generateNodes();
	//g.showNodes();
	GraphBFSTree g;
	g.generateNodes();
	g.showNodes();
	g.allNeighboursOfId(0);
	g.solve();

	int i;
	std::cin >> i;
}