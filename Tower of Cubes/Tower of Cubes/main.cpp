#include <iostream>
#include <time.h>
#include <stdio.h>
#include "Graph.h"
#include "GraphBFSTree.h"
#include "GraphDFS.h"
#include "GraphRandomWalking.h"
int Node::maxWeight = 0;


int main()
{
	srand((unsigned)time((time_t)NULL));


	if (remove("test.txt") != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");


	//Graph g;
	//g.generateNodes();
	//g.showNodes();


	GraphBFSTree g(5, 6, 100);
	g.generateNodes();
	g.showNodes();
	//g.allNeighboursOfId(0);
	g.solve();


	//GraphDFS g;
	//g.generateNodes();
	//g.showNodes();
	//g.solve();

	//GraphRandomWalking g;
	//g.generateNodes();
	//g.showNodes();
	//g.solve();


	int i;
	std::cin >> i;
}


//Czy wszystkie musz¹ siê wykonaæ jedno po drugim (na 1 zestawie danych)