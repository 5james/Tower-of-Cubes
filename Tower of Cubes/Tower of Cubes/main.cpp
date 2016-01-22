#include <iostream>
#include <time.h>
#include <stdio.h>
#include "Graph.h"
#include "GraphBFSTree.h"
#include "GraphDFS.h"
#include "GraphRandomWalking.h"
#include "Generator.h"
#include <string>
#include <sstream>
#include "declarations.h"

int Node::maxWeight = 0;
bool DEBUGINFO;

void loadAndSolve();
void generateAndShowOutput(int i, int c, int w);
void safeIntRead(int &x);

int main()
{
	srand((unsigned)time((time_t)NULL));

	std::cout << "Wybierz tryb pracy zgodnie z README\n";
	int i;
	std::cin >> i;
	
	if (i == 1)
	{
		std::cout << "Wczytuje z pliku data.txt i rozwiazuje\n";
		loadAndSolve();
	}
	else if (i == 2)
	{
		std::cout << "Podaj trzy parametry pod spacjach: ilosc szescianow, ilosc kolorow(zalecana ilosc >= ilosc szescianow), max waga\n";
		int i, c, w;

		safeIntRead(i);
		safeIntRead(c);
		safeIntRead(w);

		generateAndShowOutput(i, c, w);
	}
	else if (i == 3)
	{
		
	}
	else if (i == 99)
	{
		std::cout << "Podaj trzy parametry pod spacjach: ilosc szescianow, ilosc kolorow(zalecana ilosc >= ilosc szescianow), max waga\n";
		int i, c, w;

		safeIntRead(i);
		safeIntRead(c);
		safeIntRead(w);

		Generator g(i, c, w);
		g.generate();
	}
	else
	{
		std::cout << "Zla wartosc, koncze dzialanie programu\n";
	}


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

	//Generator g(2, 10, 10);
	//g.generate();





	std::cin >> i;
	DEBUGINFO = true;
}

void loadAndSolve()
{
	DEBUGINFO = true;
	char *name = "data.txt";

	GraphBFSTree g(name);
	g.showNodes();

	GraphDFS d(g);
	GraphRandomWalking r(g);

	g.solve();
	d.solve();
	r.solve();
}
void generateAndShowOutput(int i, int c, int w)
{
	DEBUGINFO = true;

	GraphBFSTree g(i, c, w);
	g.generateNodes();

	GraphDFS d(g);
	GraphRandomWalking r(g);

	g.solve();
	d.solve();
	r.solve();
}
void safeIntRead(int &x)
{
	std::string input = "";
	int temp;
	while (true) {
		std::cout << "Prosze wpisac liczbe: ";
		std::getline(std::cin, input);
		
		// This code converts from string to number safely.
		std::stringstream myStream(input);
		if (myStream >> temp)
			break;
		std::cout << "Zla forma liczby, prosze sprbowac ponownie: " << std::endl;
	}
	x = temp;
}