#pragma once
#include <vector>

class Node
{
private:
	int id;
	int colour;
	int weight;
	bool visited;
public:
	std::vector<Node*> neighbours;
	Node* oppositeWall;
	static int maxWeight;

	Node();
	Node(int i, int c, int w);
	~Node();
	void setId(int i);
	int getId();
	void setColour(int c);
	int getColour();
	void setWeight(int w);
	int getWeight();
	void setVisited(bool v);
	bool getVisited();

	friend std::ostream& operator<<(std::ostream& o, const Node& n);
};

