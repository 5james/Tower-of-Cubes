#include "Graph.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

void Graph::generateColoursCube(std::vector<int>& colors)
{
	for (int i = 0; i < 6; ++i)
	{
		int temp;
		bool unique;
		do
		{
			unique = true;
			temp = rand() % colours;
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
	int weight = rand() % maxWeight;
	for (int i = 0; i < 6; ++i)
	{
		nodes.push_back(Node(id, colors.at(i), weight));
	}
	addCubeNeighbourhood();
}

void Graph::addCubeNeighbourhood()
{
	nodes.at(nodes.size() - 6).neighbours.push_back(&nodes.at(nodes.size() - 5));
	if (nodes.size() > 6)
	{
		nodes.at(nodes.size() - 6).neighbours.push_back(&nodes.at(nodes.size() - 7));
		nodes.at(nodes.size() - 7).neighbours.push_back(&nodes.at(nodes.size() - 6));
	}

	nodes.at(nodes.size() - 6).oppositeWall = &(nodes.at(nodes.size() - 4));
		

	nodes.at(nodes.size() - 5).neighbours.push_back(&nodes.at(nodes.size() - 6));
	nodes.at(nodes.size() - 5).neighbours.push_back(&nodes.at(nodes.size() - 4));

	nodes.at(nodes.size() - 5).oppositeWall = &(nodes.at(nodes.size() - 2));

	nodes.at(nodes.size() - 4).neighbours.push_back(&nodes.at(nodes.size() - 5));
	nodes.at(nodes.size() - 4).neighbours.push_back(&nodes.at(nodes.size() - 3));
	nodes.at(nodes.size() - 4).neighbours.push_back(&nodes.at(nodes.size() - 2));
	nodes.at(nodes.size() - 4).neighbours.push_back(&nodes.at(nodes.size() - 1));

	nodes.at(nodes.size() - 4).oppositeWall = &(nodes.at(nodes.size() - 6));

	nodes.at(nodes.size() - 3).neighbours.push_back(&nodes.at(nodes.size() - 4));

	nodes.at(nodes.size() - 3).oppositeWall = &(nodes.at(nodes.size() - 1));

	nodes.at(nodes.size() - 2).neighbours.push_back(&nodes.at(nodes.size() - 4));

	nodes.at(nodes.size() - 2).oppositeWall = &(nodes.at(nodes.size() - 5));

	nodes.at(nodes.size() - 1).neighbours.push_back(&nodes.at(nodes.size() - 4));

	nodes.at(nodes.size() - 1).oppositeWall = &(nodes.at(nodes.size() - 3));
}

void Graph::addColourNeighbourhood()
{
	for (int i = 0; i < colours; ++i)
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
	for (int i = 0; i < cubes; ++i)
	{
		addCubeToNodes(i);
	}
	addColourNeighbourhood();
}

void Graph::loadNodes(char *name)
{
	std::ifstream myfile(name);
	if (myfile.is_open())
	{
		myfile >> cubes;
		myfile >> colours;
		myfile >> maxWeight;
		std::cout << cubes << " " << colours << " " << maxWeight << " ";
		for (int i = 0; i < cubes; ++i)
		{
			int w;
			myfile >> w;
			for (int j = 0; j < 6; ++j)
			{
				int c;
				myfile >> c;
				nodes.push_back(Node(i, c, w));
			}
			addCubeNeighbourhood();
		}
		addColourNeighbourhood();
	}
	else
	{
		std::cout << "Unable to open file";
	}

}


void Graph::showNodes()
{
	//std::ofstream myfile ("test.txt");
	//if (myfile.is_open())
	//{
	//	for (unsigned i = 0; i < nodes.size(); ++i)
	//	{
	//		myfile << nodes.at(i);
	//	}
	//	myfile << std::endl << Node::maxWeight;
	//}


	for (unsigned i = 0; i < nodes.size(); ++i)
	{
		std::cout << nodes.at(i);
	}
	std::cout << std::endl << Node::maxWeight << std::endl;
}

std::vector<Node>* Graph::getNodes()
{
	return &nodes;
}

int Graph::getCubes()
{
	return cubes;
}

int Graph::getColours()
{
	return colours;
}

int Graph::getMaxWeight()
{
	return maxWeight;
}



Graph::Graph()
{
}

Graph::Graph(Graph & g)
{
	std::vector<Node> temp(g.getNodes()->begin(), g.getNodes()->end());
	nodes = temp;
	colours = g.getColours();
	maxWeight = g.getMaxWeight();
	cubes = g.getCubes();

}

Graph::Graph(int amountOfCubes, int coloursx, int maxWeightx)
{
	colours = coloursx;
	maxWeight = maxWeightx;
	cubes = amountOfCubes;
	nodes.reserve(6 * cubes);
}

Graph::Graph(char * name)
{
	loadNodes(name);
}


Graph::~Graph()
{
}
