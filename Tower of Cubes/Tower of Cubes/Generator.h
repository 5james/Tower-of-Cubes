#pragma once
class Generator
{
private:
	int cubes, colours, maxWeight;
public:
	Generator();
	Generator(int cubes, int colours, int maxWeight);
	~Generator();
	bool generate();
};

