#include "Graph.h"
#include "declarations.h"
#include <iostream>
#include <Windows.h>


void Graph::generateColoursCube(std::vector<int>& colors)
{
	for (int i = 0; i < 6; ++i)
	{
		int temp;
		bool unique;
		do
		{
			unique = true;
			temp = rand() % COLOURS;
			for (unsigned j = 0; j < colors.size(); ++j)
			{
				if (temp == colors.at(j))
					unique = false;
			}
			//std::cout << temp << " ";
		} while (!unique);
		colors.push_back(temp);
	}
}

void Graph::addCubeToNodes(int id)
{
	std::vector<int> colors;
	generateColoursCube(colors);
	int weight = rand() % MAX_WEIGHT;
	for (int i = 0; i < 6; ++i)
	{
		nodes.push_back(Node(id, colors.at(i), weight));
	}
	addCubeNeighbourhood();
}

void Graph::addCubeNeighbourhood()
{
	nodes.at(nodes.size() - 6).neighbours.push_back(&nodes.at(nodes.size() - 5));

	nodes.at(nodes.size() - 5).neighbours.push_back(&nodes.at(nodes.size() - 6));
	nodes.at(nodes.size() - 5).neighbours.push_back(&nodes.at(nodes.size() - 4));

	nodes.at(nodes.size() - 4).neighbours.push_back(&nodes.at(nodes.size() - 5));
	nodes.at(nodes.size() - 4).neighbours.push_back(&nodes.at(nodes.size() - 3));
	nodes.at(nodes.size() - 4).neighbours.push_back(&nodes.at(nodes.size() - 2));
	nodes.at(nodes.size() - 4).neighbours.push_back(&nodes.at(nodes.size() - 1));

	nodes.at(nodes.size() - 3).neighbours.push_back(&nodes.at(nodes.size() - 4));

	nodes.at(nodes.size() - 2).neighbours.push_back(&nodes.at(nodes.size() - 4));

	nodes.at(nodes.size() - 1).neighbours.push_back(&nodes.at(nodes.size() - 4));

}

void Graph::addColourNeighbourhood()
{
	for (int i = 0; i < COLOURS; ++i)
	{
		std::vector<Node*> vec;
		for (unsigned j = 0; j < nodes.size(); ++j)
		{
			if (nodes.at(j).getColour() == i)
				vec.push_back(&nodes.at(j));
		}
		for (unsigned j = 0; j < vec.size(); ++j)
		{
			for (unsigned k = 0; k < vec.size(); ++k)
			{
				if (vec.at(j) != vec.at(k))
				{
					if (ALL_COLOURS_CONNECTED)
						vec.at(j)->neighbours.push_back(vec.at(k));
					else
					{
						if (vec.at(k)->getWeight() <= vec.at(j)->getWeight())
							vec.at(j)->neighbours.push_back(vec.at(k));
					}
				}
			}
		}
	}
}


void Graph::generateNodes()
{
	for (int i = 0; i < CUBES; ++i)
	{
		addCubeToNodes(i);
	}
	addColourNeighbourhood();
}

void Graph::showNodes()
{
	for (unsigned i = 0; i < nodes.size(); ++i)
	{
		std::cout << nodes.at(i);
	}
}

Graph::Graph()
{
	nodes.reserve(6 * CUBES);
}


Graph::~Graph()
{
}
