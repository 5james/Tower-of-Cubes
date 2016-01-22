#include "GraphDFS.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

//	TODO:
//		1. zrób vector w DFS, ¿ebyœ wiedzia³ które wierzcho³ki by³y na dole
//		2. jak zrobisz 1. to dodaj do if w 38 linii warunek, ¿e mo¿esz dodaæ tylko do przeciwleg³eœ œciany tamtego
//			w przeciwnym razie return??
//		3. Dodaj mo¿liwoœæ koñczenia wczeœniej



bool GraphDFS::cubeIsNotVisited(std::vector<std::pair<int, Node*> >& cubesVisited, int id)
{
	for (unsigned i = 0; i < cubesVisited.size(); ++i)
	{
		if (id == cubesVisited.at(i).first)
			return false;
	}
	return true;
}

void GraphDFS::DFS(	Node *actual,
					std::vector<std::pair<int, Node*> >& cubesVisited,
					std::vector<std::pair<int, Node*> >& maxTower,
					bool inside,
					int nested
					)
{

	if (nested > 2)
		return;

	actual->setVisited(true);

	bool added = false;

	if (cubesVisited.empty())
	{
		cubesVisited.push_back(std::make_pair(actual->getId(),actual) );
		nested = 0;
		added = true;

		DFS(actual->oppositeWall, cubesVisited, maxTower, true, 0);
		
	}
		
	bool skip = false;
	if (!cubesVisited.empty() &&
		actual->getId() != cubesVisited.back().first &&
		inside == false &&
		actual->getColour() == cubesVisited.back().second->oppositeWall->getColour() &&
		actual->getWeight() <= cubesVisited.back().second->oppositeWall->getWeight()
		)
	{
		cubesVisited.push_back(std::make_pair(actual->getId(), actual) );
		nested = 0;
		added = true;

		DFS(actual->oppositeWall, cubesVisited, maxTower, true, 0);
		skip = true;

		//TODO tutaj zrob DFS do przeciwleglego wierzcholka i return
		//DFS(actual->neighbours.at(i), cubesVisited, maxTower, false, 0);
		//return
	}
		

	////debug
	//std::ofstream myfile ("test.txt", std::ios_base::app);
	//if (myfile.is_open())
	//{
	//	myfile << std::endl << cubesVisited.size() << " < wielkosc >> ";
	//	for (unsigned i = 0; i < cubesVisited.size(); ++i)
	//	{
	//		myfile << cubesVisited.at(i) << " ";
	//	}
	//}


	if (!skip)
	{
		for (unsigned i = 0; i < actual->neighbours.size(); ++i)
		{
			//if (actual->neighbours.at(i)->getId() == actual->getId()
			//	&& actual->neighbours.at(i)->getVisited() == false)
			//{
			//	DFS(actual->neighbours.at(i), cubesVisited, maxTower, true, nested + 1);
			//}
			if (actual->getColour() == actual->neighbours.at(i)->getColour()
				&& actual->neighbours.at(i)->getId() != actual->getId()
				&& actual->neighbours.at(i)->getVisited() == false
				&& cubeIsNotVisited(cubesVisited, actual->neighbours.at(i)->getId())
				)
			{
				DFS(actual->neighbours.at(i), cubesVisited, maxTower, false, 0);
			}
		}
	}
	actual->setVisited(false);

	if (inside == false && added == true)
		cubesVisited.pop_back();
	if (cubesVisited.size() > maxTower.size())
	{
		maxTower = cubesVisited;
	}
}

GraphDFS::GraphDFS(int amountOfCubes, int coloursx, int maxWeightx) : Graph(amountOfCubes, coloursx, maxWeightx)
{
}

GraphDFS::GraphDFS(GraphBFSTree &g) : Graph(g)
{
}

GraphDFS::~GraphDFS()
{
}

void GraphDFS::solve()
{
	std::vector<std::pair<int, Node*> > maxTower;
	for (unsigned i = 0; i < nodes.size(); ++i)
	{
		std::vector<std::pair<int, Node*> > tempTower;
		std::vector<std::pair<int, Node*> > tempMaxTower;

		for (auto j = nodes.begin(); j != nodes.end(); ++j)
		{
			j->setVisited(false);
		}

		if (nodes.at(i).getWeight() == Node::maxWeight)
		{
			DFS(&(nodes.at(i)), tempTower, tempMaxTower, false, 0);
		}
		if (tempMaxTower.size() > maxTower.size())
		{
			maxTower = tempMaxTower;
			std::cout << std::endl << "Zmieniam dla " << i;
		}
		if (tempMaxTower.size() == cubes)
		{
			std::cout << std::endl << "Dla node " << i << " " << maxTower.size();

			break;
		}

		//std::cout << std::endl;
		//for (unsigned i = 0; i < tempMaxTower.size(); ++i)
		//{
		//	std::cout << tempMaxTower.at(i) << " ";
		//}


		std::cout << std::endl << "Dla node " << i << " " << maxTower.size();

	}

	std::cout << std::endl << "TOWER \t\t";
	for (unsigned i = 0; i < maxTower.size(); ++i)
	{
		std::cout << maxTower.at(i).first << " ";
	}
	std::cout << std::endl << "COLOURS \t";
	for (unsigned i = 0; i < maxTower.size(); ++i)
	{
		std::cout << maxTower.at(i).second->getColour() << " ";
	}
}


