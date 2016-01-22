#include <iostream>
#include <time.h>
#include <stdio.h>
#include "Graph.h"
#include "GraphBFSTree.h"
#include "GraphDFS.h"
#include "GraphRandomWalking.h"
#include "Generator.h"
int Node::maxWeight = 0;



int main()
{
	srand((unsigned)time((time_t)NULL));
	
	//std::cout << "Wybierz tryb pracy zgodnie z README\n";
	//int i;
	//std::cin >> i;


	//if (remove("test.txt") != 0)
	//	perror("Error deleting file");
	//else
	//	puts("File successfully deleted");



	//GraphBFSTree g(700, 700, 700);
	//g.generateNodes();
	//std::cout << "juz" << std::endl;
	//GraphDFS c(g);
	//GraphRandomWalking s(g);

	//g.solve();
	//c.solve();
	//s.solve();

	Generator mygen(200, 200, 200);
	mygen.generate();

	int i;
	std::cin >> i;
}
