// Wieza N szescianow
// autor: Jakub Guzek
// ver 0.1

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

