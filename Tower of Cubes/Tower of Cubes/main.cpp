// Wieza N szescianow
// autor: Jakub Guzek
// ver 0.1

#include <iostream>
#include <algorithm> // max
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
void generateAndTableN(int choice2);
void generateAndTableK(int choice2);
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
		std::cout << "Wybierz zaleznosci od:\n";
		std::cout << "1. Liczby N szescianow\n";
		std::cout << "2. Liczby K kolorow\n";
		int choice1;
		safeIntRead(choice1);

		std::cout << "Wybierz jeden algorytm\n";
		std::cout << "1. BFS\n";
		std::cout << "2. DFS\n";
		std::cout << "3. RandomWalking\n";
		int choice2;
		safeIntRead(choice2);

		if (choice1 == 1)
			generateAndTableN(choice2);
		else if (choice1 == 2)
			generateAndTableK(choice2);
	}
	else if (i == 99)
	{
		std::cout << "Podaj trzy parametry pod enterach: \nilosc szescianow, \nilosc kolorow(zalecana ilosc >= ilosc szescianow), \nmax waga\n";
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

	getchar();
}

void generateAndTableN(int choice)
{
	int retests = 2;
	if (choice == 1)
	{
		Table::getInstance().bfs500();
		retests = 4;
		std::cout << "ODLICZANIE przy 5000 kolorach i maxymalnej wadze 2000:" << std::endl;
	}
	else if (choice == 2)
	{
		Table::getInstance().dfs500();
		std::cout << "ODLICZANIE przy 1000 kolorach i maxymalnej wadze 2000:" << std::endl;
	}
	else if (choice == 3)
	{
		Table::getInstance().random500();
		std::cout << "ODLICZANIE przy 1000 kolorach i maxymalnej wadze 2000:" << std::endl;
	}

	for (int i = 0; i < NOTESTS; ++i)
	{
		std::cout << NOTESTS - i << "\t" << (Table::getInstance().getNoPrisms(i)) << std::endl;
		clock_t t = 0;
		DEBUGINFO = true;
		for (int j = 0; j < retests; ++j)
		{
			Node::maxWeight = 0;
			Graph *g;

			if (choice == 1)
			{
				g = new GraphBFSTree(Table::getInstance().getNoPrisms(i), 5000, 2000);
			}
			else if (choice == 2)
			{
				g = new GraphDFS(Table::getInstance().getNoPrisms(i), 1000, 2000);
			}
			else if (choice == 3)
			{
				g = new GraphRandomWalking(Table::getInstance().getNoPrisms(i), 1000, 2000);
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
			t = std::max(tm, t);
			Table::getInstance().setTn(i, t);
		}
	}
	for (int i = 0; i < NOTESTS; ++i)
		Table::getInstance().setQn(i);
	Table::getInstance().drawTable();
}


void generateAndTableK(int choice)
{
	int retests = 1;
	if (choice == 1)
	{
		Table::getInstance().bfs100K(100);
		retests = 1;
		std::cout << "ODLICZANIE przy 100 szescianach i maxymalnej wadze 2000:" << std::endl;
	}
	else if (choice == 2)
	{
		Table::getInstance().dfs100K(100);
		std::cout << "ODLICZANIE przy 100 szescianach i maxymalnej wadze 2000:" << std::endl;
	}
	else if (choice == 3)
	{
		Table::getInstance().random100K(100);
		std::cout << "ODLICZANIE przy 100 szescianach i maxymalnej wadze 2000:" << std::endl;
	}

	for (int i = 0; i < NOTESTS; ++i)
	{
		std::cout << NOTESTS - i << "\t" << (Table::getInstance().getNoPrisms(i)) << std::endl;
		clock_t t = 0;
		DEBUGINFO = true;
		for (int j = 0; j < retests; ++j)
		{
			Node::maxWeight = 0;
			Graph *g;

			if (choice == 1)
			{
				g = new GraphBFSTree(100, (Table::getInstance().getNoPrisms(i)), 2000);
			}
			else if (choice == 2)
			{
				g = new GraphDFS(100, (Table::getInstance().getNoPrisms(i)), 2000);
			}
			else if (choice == 3)
			{
				g = new GraphRandomWalking(100, (Table::getInstance().getNoPrisms(i)), 2000);
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
			t = std::max(tm, t);
			Table::getInstance().setTn(i, t);
		}
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

	getchar();
}
void generateAndShowOutput(int i, int c, int w)
{
	DEBUGINFO = true;

	GraphBFSTree g(i, c, w);
	g.generateNodes();
	g.showNodes();

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
