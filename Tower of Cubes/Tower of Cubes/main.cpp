#include <iostream>
#include <time.h>
#include "Graph.h"

int main()
{
	srand((unsigned)time((time_t)NULL));
	Graph g;
	g.generateNodes();
	g.showNodes();
	int i;
	std::cin >> i;
}