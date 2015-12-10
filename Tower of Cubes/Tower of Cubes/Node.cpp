#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <algorithm> 

Node::Node()
{
	visited = false;
}

Node::Node(int i, int c, int w)
{
	id = i;
	colour = c;
	weight = w;
	maxWeight = std::max(maxWeight, w);
	visited = false;
}


Node::~Node()
{
}

void Node::setId(int i)
{
	id = i;
}

int Node::getId()
{
	return id;
}

void Node::setColour(int c)
{
	colour = c;
}

int Node::getColour()
{
	return colour;
}

void Node::setWeight(int w)
{
	weight = w;
}

int Node::getWeight()
{
	return weight;
}

void Node::setVisited(bool v)
{
	visited = v;
}

bool Node::getVisited()
{
	return visited;
}

std::ostream& operator<<(std::ostream& o, const Node& n)
{
	o << "[" << n.id << "][" << n.colour << "][" << n.weight << "] " << n.neighbours.size() << "   ";
	for (unsigned i = 0; i < n.neighbours.size(); ++i)
	{
		o << "[" << n.neighbours.at(i)->getId() << "][" << n.neighbours.at(i)->getColour() << "][" << n.neighbours.at(i)->getWeight() << "] ";
	}
	o << std::endl;
	return o;
}
