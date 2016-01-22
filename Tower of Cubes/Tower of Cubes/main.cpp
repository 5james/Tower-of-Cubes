#include <iostream>
#include <time.h>
#include <stdio.h>
#include "Graph.h"
#include "GraphBFSTree.h"
#include "GraphDFS.h"
#include "GraphRandomWalking.h"
#include "Generator.h"
#include "Table.h"
#include <string>
#include <sstream>
#include <ctime>
#include "declarations.h"

int Node::maxWeight = 0;
bool DEBUGINFO;

void loadAndSolve();
void generateAndShowOutput(int i, int c, int w);
void generateAndTable(int choice);
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
		int j, c, w;

		safeIntRead(j);
		safeIntRead(c);
		safeIntRead(w);

		generateAndShowOutput(j, c, w);
	}
	else if (i == 3)
	{
		std::cout << "Wybierz jeden algorytm\n";
		std::cout << "1. BFS\n";
		std::cout << "2. DFS\n";
		std::cout << "3. RandomWalking\n";
		int choice;
		safeIntRead(choice);

		generateAndTable(choice);
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

	std::cin >> i;
	DEBUGINFO = true;
}

void generateAndTable(int choice)
{
	if (choice == 1)
	{
		Table::getInstance().bfs();
	}
	else if (choice == 2)
	{
		Table::getInstance().dfs();
	}
	else if (choice == 3)
	{
		Table::getInstance().random();
	}

	for (int i = 0; i < NOTESTS; ++i)
	{
		std::cout << NOTESTS - i - 1 << std::endl;
		Graph *g;

		if (choice == 1)
		{
			g = new GraphBFSTree(Table::getInstance().getNoPrisms(i), Table::getInstance().getNoPrisms(i), Table::getInstance().getNoPrisms(i));
		}
		else if (choice == 2)
		{
			g = new GraphDFS(Table::getInstance().getNoPrisms(i), Table::getInstance().getNoPrisms(i), Table::getInstance().getNoPrisms(i));
		}
		else if (choice == 3)
		{
			g = new GraphRandomWalking(Table::getInstance().getNoPrisms(i), Table::getInstance().getNoPrisms(i), Table::getInstance().getNoPrisms(i));
		}
		else
		{
			std::cout << "Bledna dana, koncze program";
			return;
		}
		g->generateNodes();
		clock_t start = clock();
		g->solve();
		clock_t koniec = clock();
		clock_t tm = koniec - start;

		Table::getInstance().setTn(i, tm);
	}
	for (int i = 0; i < NOTESTS; ++i)
		Table::getInstance().setQn(i);
	Table::getInstance().drawTable();
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
