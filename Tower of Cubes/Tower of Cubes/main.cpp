#include <iostream>
#include <time.h>
#include "Graph.h"
#include "GraphBFSTree.h"
#include "GraphDFS.h"
int Node::maxWeight = 0;


int main()
{
	srand((unsigned)time((time_t)NULL));
	//Graph g;
	//g.generateNodes();
	//g.showNodes();

	//GraphBFSTree g;
	//g.generateNodes();
	//g.showNodes();
	//g.allNeighboursOfId(0);
	//g.solve();

	GraphDFS g;
	g.generateNodes();
	g.showNodes();
	g.solve();

	int i;
	std::cin >> i;
}


//Czy wszystkie musz¹ siê wykonaæ jedno po drugim (na 1 zestawie danych)