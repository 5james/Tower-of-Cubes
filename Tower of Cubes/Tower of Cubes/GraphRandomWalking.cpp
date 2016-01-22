#include "GraphRandomWalking.h"
#include <iostream>
#include <Windows.h>
#include <fstream>



bool GraphRandomWalking::cubeIsNotVisited(std::vector<int>& cubesVisited, int id)
{
	for (unsigned i = 0; i < cubesVisited.size()-1; ++i)
	{
		if (id == cubesVisited.at(i))
			return false;
	}
	return true;
}

void GraphRandomWalking::RandomWalking(Node *actual, std::vector<int>& cubesVisited)
{

	bool thereAreNeighbours = false;
	for (unsigned i = 0; i < actual->neighbours.size(); ++i)
	{
		if (actual->neighbours.at(i)->getColour() != actual->getColour())
			thereAreNeighbours = true;
	}
	cubesVisited.push_back(actual->getId());

	while (thereAreNeighbours)
	{
		actual->setVisited(true);


		if (actual->getId() != cubesVisited.back())
			cubesVisited.push_back(actual->getId());

		std::vector<Node*> possibleNext;
		for (unsigned i = 0; i < actual->neighbours.size(); ++i)
		{
			if (actual->neighbours.at(i)->getVisited() == false 
				&& cubeIsNotVisited(cubesVisited, actual->neighbours.at(i)->getId()) 
				&& actual->getWeight() >= actual->neighbours.at(i)->getWeight()
				)
				possibleNext.push_back(actual->neighbours.at(i));
		}
		if (!possibleNext.empty())
		{
			//std::cout << std::endl;
			//for (unsigned i = 0; i < possibleNext.size(); ++i)
			//{
			//	std::cout << possibleNext.at(i)->getId() << " ";
			//}
			int drawn = (int)(rand() % possibleNext.size());
			actual = possibleNext.at(drawn);
		}
		else
			thereAreNeighbours = false;
	}
}

void GraphRandomWalking::solve()
{
	std::vector<int> maxTower;
	for (unsigned i = 0; i < nodes.size(); ++i)
	{
		std::vector<int> tempTower;

		for (auto j = nodes.begin(); j != nodes.end(); ++j)
		{
			j->setVisited(false);
		}

		if (nodes.at(i).getWeight() == Node::maxWeight)
		{
			RandomWalking(&(nodes.at(i)), tempTower);
		}
		if (tempTower.size() > maxTower.size())
		{
			maxTower = tempTower;
			std::cout << std::endl << " Zmieniam dla " << i;
		}
		std::cout << std::endl << "Dla node " << i << " " << maxTower.size();
	}

	std::cout << std::endl << maxTower.size() << std::endl;
	for (unsigned i = 0; i < maxTower.size(); ++i)
	{
		std::cout << maxTower.at(i) << " ";
	}
}


