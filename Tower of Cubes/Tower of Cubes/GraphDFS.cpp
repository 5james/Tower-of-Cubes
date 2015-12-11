#include "declarations.h"
#include "GraphDFS.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

//	TODO:
//		1. zr�b vector w DFS, �eby� wiedzia� kt�re wierzcho�ki by�y na dole
//		2. jak zrobisz 1. to dodaj do if w 38 linii warunek, �e mo�esz doda� tylko do przeciwleg�e� �ciany tamtego
//			w przeciwnym razie return??



bool GraphDFS::cubeIsNotVisited(std::vector<int>& cubesVisited, int id)
{
	for (unsigned i = 0; i < cubesVisited.size(); ++i)
	{
		if (id == cubesVisited.at(i))
			return false;
	}
	return true;
}

void GraphDFS::DFS(Node *actual, std::vector<int>& cubesVisited, std::vector<int>& maxTower, bool inside, int nested)
{

	if (nested > 2)
		return;

	actual->setVisited(true);

	if (cubesVisited.empty())
	{
		cubesVisited.push_back(actual->getId());
		nested = 0;
	}
		

	if (!cubesVisited.empty() 
		&& actual->getId() != cubesVisited.back() 
		&& inside == false
		)
	{
		cubesVisited.push_back(actual->getId());
		nested = 0;
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



	for (unsigned i = 0; i < actual->neighbours.size(); ++i)
	{
		if (actual->neighbours.at(i)->getId() == actual->getId()
			&& actual->neighbours.at(i)->getVisited() == false)
		{
			DFS(actual->neighbours.at(i), cubesVisited, maxTower, true, nested+1);
		}
		if ( actual->getColour() == actual->neighbours.at(i)->getColour()
			&& actual->neighbours.at(i)->getId() != actual->getId()
			&& actual->neighbours.at(i)->getVisited() == false
			&& cubeIsNotVisited(cubesVisited, actual->neighbours.at(i)->getId())
			)
		{
			DFS(actual->neighbours.at(i), cubesVisited, maxTower, false, 0);
		}
	}

	actual->setVisited(false);
	if (inside == false)
		cubesVisited.pop_back();

	if (cubesVisited.size() > maxTower.size())
	{
		maxTower = cubesVisited;
	}

}

void GraphDFS::solve()
{
	std::vector<int> maxTower;
	for (unsigned i = 0; i < nodes.size(); ++i)
	{
		std::vector<int> tempTower;
		std::vector<int> tempMaxTower;

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
			std::cout << "Zmieniam dla " << i;
		}

		//std::cout << std::endl;
		//for (unsigned i = 0; i < tempMaxTower.size(); ++i)
		//{
		//	std::cout << tempMaxTower.at(i) << " ";
		//}
		std::cout << std::endl << "Dla node " << i << " " << maxTower.size();
	}

	std::cout << std::endl;
	for (unsigned i = 0; i < maxTower.size(); ++i)
	{
		std::cout << maxTower.at(i) << " ";
	}
}


