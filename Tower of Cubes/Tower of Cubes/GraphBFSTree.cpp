// Wieza N szescianow
// autor: Jakub Guzek
// ver 0.1

#include "GraphBFSTree.h"
#include <utility>
#include <list>
#include <vector>
#include <algorithm> 
#include <iostream>
#include "declarations.h"


//void GraphBFSTree::colorOnBottom(SimpleNodesTree *& current)
//{
//	if (current->depth > 0)
//	{
//		bool found = false;
//		std::vector<int> colorsOfCurrent;
//		for (unsigned i = 0; i < nodes.size(); ++i)
//		{
//			if (nodes.at(i).getId() == current->id)
//			{
//				colorsOfCurrent.push_back(nodes.at(i).getColour());
//			}
//		}
//		for (unsigned i = 0; i < nodes.size(); ++i)
//		{
//			if (nodes.at(i).getId() == current->parent->id)
//			{
//				for (unsigned j = 0; j < colorsOfCurrent.size(); ++j)
//				{
//					if (nodes.at(i).getColour() == colorsOfCurrent.at(j))
//					{
//						current->bottomColor = colorsOfCurrent.at(j);
//						found = true;
//					}
//
//				}
//			}
//		}
//		if (!found)
//			current->bottomColor = -1;
//	}
//}


// allNeighboursOfId returns vector of id of all neighbours with same colour (oppositewalls)
std::vector<std::pair<int, int>> GraphBFSTree::allNeighboursOfIdWithColour(int id, int colourOnBottom)
{
	std::vector<Node*> nodeWithIdAndColour;

	// szukam wszystkie node ktorych id zgadza sie z arg1 - id
	if (colourOnBottom != -1) // przypadek, ze nie jest rootem, wiec musze zamienic znaleziony node na sasiednia strone
	{
		for (unsigned i = 0; i < nodes.size(); ++i) // saving all nodes with id = id(arg) && colour
		{
			if (nodes.at(i).getId() == id &&			// chcemy node z tym samym id
				nodes.at(i).getColour() == colourOnBottom	// i kolor te¿ ten sam
				)
			{
				nodeWithIdAndColour.push_back(nodes.at(i).oppositeWall);
			}
		}
	}
	else // przypadek, ze jest rootem, wiec nie musze zamieniac scian - przetwarzam wszystkie 6
	{
		for (unsigned i = 0; i < nodes.size(); ++i) // saving all nodes with id = id(arg)
		{
			if (nodes.at(i).getId() == id			// chcemy node z tym samym id
				)
			{
				nodeWithIdAndColour.push_back(nodes.at(i).oppositeWall);
			}
		}
	}


	std::vector<Node*> neighbourNodes;
	for (unsigned i = 0; i < nodeWithIdAndColour.size(); ++i)
	{
		for (unsigned j = 0; j < nodeWithIdAndColour.at(i)->neighbours.size(); ++j)
		{
			if (nodeWithIdAndColour.at(i)->getColour() == nodeWithIdAndColour.at(i)->neighbours.at(j)->getColour() &&
				nodeWithIdAndColour.at(i)->getWeight() >= nodeWithIdAndColour.at(i)->neighbours.at(j)->getWeight()
				)
				neighbourNodes.push_back(nodeWithIdAndColour.at(i)->neighbours.at(j));
		}
	}

	std::vector<std::pair<int, int>> result;
	for (unsigned i = 0; i < neighbourNodes.size(); ++i)
	{
		std::pair<int, int> x;
		x = std::make_pair(neighbourNodes.at(i)->getId(), neighbourNodes.at(i)->getColour());
		result.push_back(x);
	}
	//std::cout << std::endl;
	//for (auto i = result.begin(); i != result.end(); ++i)
	//{
	//	std::cout << (*i) << " ";
	//}
	return result;
}

bool GraphBFSTree::checkOppositeWallsColour(SimpleNodesTree* toCheck)
{
	if (toCheck->depth < 1)
		return true;
	if (toCheck->depth >= 1)
	{

	}
	return false;
}


//zwraca true jesli w galezi (od toCheck do root) nie ma node'a ktory posiada id (arg1)
bool GraphBFSTree::isIdUnique(int id, SimpleNodesTree* toCheck)
{
	SimpleNodesTree *actual = toCheck;
	while (actual->parent != NULL)
	{
		if (actual->parent->id == id)
			return false;
		actual = actual->parent;
	}

	return true;
}

GraphBFSTree::~GraphBFSTree()
{
}


GraphBFSTree::GraphBFSTree(int amountOfCubes, int coloursx, int maxWeightx) : Graph(amountOfCubes, coloursx, maxWeightx)
{

}

GraphBFSTree::GraphBFSTree(Graph & g): Graph(g)
{
}

GraphBFSTree::GraphBFSTree(char * name): Graph(name)
{
}

void GraphBFSTree::solve()
{
	std::vector<int> starters;

	std::vector<std::pair<int, int> > tower;

	for (unsigned i = 0; i < nodes.size(); ++i)
	{
		if (nodes.at(i).getWeight() == Node::maxWeight)
		{
			int id = nodes.at(i).getId();
			if (starters.empty())
				starters.push_back(id);
			else
			{
				if (starters.back() != id)
					starters.push_back(id);
			}

		}
	}

	for (unsigned i = 0; i < starters.size(); ++i)
	{

		SimpleNodesTree* root = new SimpleNodesTree();
		(*root).id = starters.at(i);
		(*root).depth = 0;
		(*root).parent = NULL;
		(*root).bottomColor = -1;
		std::vector<SimpleNodesTree*> toDo;
		toDo.push_back(root);
		std::vector<SimpleNodesTree*> toDestroy;
		toDestroy.push_back(root);
		SimpleNodesTree *lastLeaf = root;
		int size = 0;

		while (!toDo.empty())
		{
			size++;
			//std::cout << size << " zaglebienie" << std::endl;

			lastLeaf = toDo.at(0);
			std::vector<SimpleNodesTree*> nextToDo;
			for (unsigned j = 0; j < toDo.size(); ++j)
			{
				std::vector<std::pair<int, int>> toDoNeighbourhood = allNeighboursOfIdWithColour(toDo.at(j)->id, toDo.at(j)->bottomColor);
				for (unsigned k = 0; k < toDoNeighbourhood.size(); ++k)
				{
					if (isIdUnique(toDoNeighbourhood.at(k).first, toDo.at(j)))
					{


						SimpleNodesTree *next = new SimpleNodesTree();

						next->id = toDoNeighbourhood.at(k).first;
						next->depth = toDo.at(j)->depth + 1;
						next->parent = toDo.at(j);
						next->bottomColor = toDoNeighbourhood.at(k).second;


						toDo.at(j)->child.push_back(next);
						nextToDo.push_back(next);
						toDestroy.push_back(next);
					}
				}
			}
			toDo = nextToDo;
		}

		//correction of root colour
		SimpleNodesTree *rootCorrector = lastLeaf;
		while (rootCorrector->parent->parent)
			rootCorrector = rootCorrector->parent;
		Node* tempNode = NULL;
		int tempColour = rootCorrector->bottomColor;
		rootCorrector = rootCorrector->parent;
		for (unsigned i = 0; i < nodes.size(); ++i)
		{
			if (nodes.at(i).getColour() == tempColour &&
				nodes.at(i).getId() == rootCorrector->id
				)
			{
				tempNode = &nodes.at(i);
			}
		}
		if (tempNode != NULL)
		{
			rootCorrector->bottomColor = tempNode->oppositeWall->getColour();
		}

		if ((unsigned)size > tower.size())
		{
			std::vector<std::pair<int, int> > higher;
			while (lastLeaf->parent)
			{
				higher.push_back(std::make_pair(lastLeaf->id, lastLeaf->bottomColor));
				lastLeaf = lastLeaf->parent;
			}
			if (lastLeaf)
			{
				higher.push_back(std::make_pair(lastLeaf->id, lastLeaf->bottomColor));
			}
			tower = higher;

		}


		for (unsigned l = 0; l < toDestroy.size(); ++l)
			delete toDestroy.at(l);
	}


	std::reverse(tower.begin(), tower.end());

	if (DEBUGINFO == true)
	{
		std::cout << std::endl << "TOWER \t\t";
		for (unsigned idx = 0; idx < tower.size(); ++idx)
		{
			std::cout << tower.at(idx).first << " ";
		}
		std::cout << std::endl << "COLOUR BOTTOM \t";
		for (unsigned idx = 0; idx < tower.size(); ++idx)
		{
			std::cout << tower.at(idx).second << " ";
		}
		std::cout << std::endl;
	}
}


