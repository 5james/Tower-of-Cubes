// Wieza N szescianow
// autor: Jakub Guzek
// ver 0.1

#include "GraphRandomWalking.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "declarations.h"


bool GraphRandomWalking::cubeIsNotVisited(std::vector<std::pair<int, Node*> >& cubesVisited, int id)
{
	for (unsigned i = 0; i < cubesVisited.size()-1; ++i)
	{
		if (id == cubesVisited.at(i).first)
			return false;
	}
	return true;
}

void GraphRandomWalking::RandomWalking(Node *actual, std::vector<std::pair<int, Node*> >& cubesVisited)
{

	bool thereAreNeighbours = false;
	for (unsigned i = 0; i < actual->neighbours.size(); ++i)
	{
		if (actual->neighbours.at(i)->getColour() != actual->getColour())
			thereAreNeighbours = true;
	}
	std::pair<int, Node*> temp;
	temp = std::make_pair(actual->getId(), actual);
	cubesVisited.push_back(temp);

	while (thereAreNeighbours)
	{
		actual->setVisited(true);


		if (actual->getId() != cubesVisited.back().first)
		{
			std::pair<int, Node*> temp2;
			temp2 = std::make_pair(actual->getId(), actual);
			cubesVisited.push_back(temp2);
		}

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

GraphRandomWalking::GraphRandomWalking(int amountOfCubes, int coloursx, int maxWeightx) : Graph(amountOfCubes, coloursx, maxWeightx)
{
}

GraphRandomWalking::GraphRandomWalking(Graph & g) : Graph(g)
{
}

GraphRandomWalking::GraphRandomWalking(char * name) : Graph(name)
{
}

GraphRandomWalking::GraphRandomWalking()
{
}

GraphRandomWalking::~GraphRandomWalking()
{
}

void GraphRandomWalking::solve()
{
	std::vector<std::pair<int, Node*> > maxTower;
	for (unsigned i = 0; i < nodes.size(); ++i)
	{
		std::vector<std::pair<int, Node*> > tempTower;

		for (auto j = nodes.begin(); j != nodes.end(); ++j)
		{
			j->setVisited(false);
		}

		//if (nodes.at(i).getWeight() == Node::maxWeight)
		{
			RandomWalking(&(nodes.at(i)), tempTower);
		}
		if (tempTower.size() > maxTower.size())
		{
			maxTower = tempTower;
			//std::cout << std::endl << " Zmieniam dla " << i;
		}
		//std::cout << std::endl << "Dla node " << i << " " << maxTower.size();
	}

	if (DEBUGINFO == true)
	{
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
		std::cout << std::endl;
	}
}


