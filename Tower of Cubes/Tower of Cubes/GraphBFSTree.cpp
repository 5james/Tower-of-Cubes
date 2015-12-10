#include "GraphBFSTree.h"
#include <utility>
#include <list>
#include <iostream>

std::vector<int> GraphBFSTree::allNeighboursOfId(int id)
{
	std::vector<Node*> nodesWithId;
	for (unsigned i = 0; i < nodes.size(); ++i) // saving all nodes with id = id(arg)
	{
		if (nodes.at(i).getId() == id)
			nodesWithId.push_back(&nodes.at(i));
	} 
	std::vector<Node*> neighbourNodes;
	for (unsigned i = 0; i < nodesWithId.size(); ++i)
	{
		for (unsigned j = 0; j < nodesWithId.at(i)->neighbours.size(); ++j)
		{
			if (nodesWithId.at(i)->getColour() == nodesWithId.at(i)->neighbours.at(j)->getColour() 
				//&& nodesWithId.at(i)->getWeight() >= nodesWithId.at(i)->neighbours.at(j)->getWeight())
				)
				neighbourNodes.push_back(nodesWithId.at(i)->neighbours.at(j));
		}
	}

	std::list<int> listResult;
	for (unsigned i = 0; i < neighbourNodes.size(); ++i)
	{
		listResult.push_back(neighbourNodes.at(i)->getId());
	}

	listResult.sort();
	listResult.unique();
	std::vector<int> result{ std::begin(listResult), std::end(listResult) };
	//std::cout << std::endl;
	//for (auto i = result.begin(); i != result.end(); ++i)
	//{
	//	std::cout << (*i) << " ";
	//}
	return result;
}

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

void GraphBFSTree::solve()
{
	std::vector<int> starters;

	std::vector<int> tower;

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
		(*root).parent = NULL;
		std::vector<SimpleNodesTree*> toDo;
		toDo.push_back(root);
		std::vector<SimpleNodesTree*> toDestroy;
		SimpleNodesTree *lastLeaf = root;
		int size = 0;
		while (!toDo.empty())
		{
			size++;

			for (unsigned j = 0; j < toDo.size(); ++j)
			{
				toDestroy.push_back(toDo.at(j));
			}

			lastLeaf = toDo.at(0);
			std::vector<SimpleNodesTree*> nextToDo;
			for (unsigned j = 0; j < toDo.size(); ++j)
			{
				std::vector<int> toDoNeighbourhood = allNeighboursOfId(toDo.at(j)->id);
				for (unsigned k = 0; k < toDoNeighbourhood.size(); ++k)
				{
					if (isIdUnique(toDoNeighbourhood.at(k), toDo.at(j)))
					{
						SimpleNodesTree *next = new SimpleNodesTree();
						next->id = toDoNeighbourhood.at(k);
						next->parent = toDo.at(j);
						toDo.at(j)->child.push_back(next);
						nextToDo.push_back(next);
					}
				}
			}
			toDo = nextToDo;
		}
		if ((unsigned)size > tower.size())
		{
			std::vector<int> higher;
			while (lastLeaf->parent)
			{
				higher.push_back(lastLeaf->id);
				lastLeaf = lastLeaf->parent;
			}
			tower = higher;
				
		}



		for (unsigned l = 0; l < toDestroy.size(); ++l)
			delete toDestroy.at(l);
	}

	std::cout << std::endl;
	for (unsigned idx = 0; idx < tower.size(); ++idx)
	{
		std::cout << tower.at(idx) << " ";
	}
}


