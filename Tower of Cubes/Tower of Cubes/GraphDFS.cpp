#include "declarations.h"
#include "GraphDFS.h"
#include <iostream>



void GraphDFS::DFS(Node *actual, std::vector<int>& cubesVisited, std::vector<int>& maxTower, bool inside)
{
	actual->setVisited(true);

	if(cubesVisited.empty())
		cubesVisited.push_back(actual->getId());

	if (!cubesVisited.empty() && actual->getId() != cubesVisited.back() && inside == false)
		cubesVisited.push_back(actual->getId());

	////debug
	//std::cout << std::endl;
	//for (auto j = cubesVisited.begin(); j != cubesVisited.end(); ++j)
	//{
	//	std::cout << *j << " ";
	//}


	for (unsigned i = 0; i < actual->neighbours.size(); ++i)
	{
		if (actual->neighbours.at(i)->getId() == actual->getId() 
			&& actual->neighbours.at(i)->getVisited() == false)
		{
			DFS(actual->neighbours.at(i), cubesVisited, maxTower, true);
		}
		if (actual->getColour() == actual->neighbours.at(i)->getColour() 
			&& actual->neighbours.at(i)->getId() != actual->getId() 
			&& actual->neighbours.at(i)->getVisited() == false)
		{
			DFS(actual->neighbours.at(i), cubesVisited, maxTower, false);
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
	std::cout << std::endl << &(nodes.at(0));
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
			DFS(&(nodes.at(i)), tempTower, tempMaxTower, false);
		}
		if (tempMaxTower.size() > maxTower.size())
		{
			maxTower = tempMaxTower;
		}
	}
	
	std::cout << std::endl;
	for (unsigned i = 0; i < maxTower.size(); ++i)
	{
		std::cout << maxTower.at(i) << " ";
	}
}


