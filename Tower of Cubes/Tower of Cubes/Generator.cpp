// Wieza N szescianow
// autor: Jakub Guzek
// ver 0.1

#include "Generator.h"
#include <fstream>
#include <iostream>
#include <vector>



Generator::Generator()
{
	cubes = colours = maxWeight = 100;
}

Generator::Generator(int cubesx, int coloursx, int maxWeightx) : cubes(cubesx), colours(coloursx), maxWeight(maxWeightx)
{
}


Generator::~Generator()
{
}

bool Generator::generate()
{
	std::ofstream myfile("data.txt");
	if (myfile.is_open())
	{
		myfile << cubes << " "<<  colours << " " << maxWeight << "\n";
		for (int i = 0; i < cubes; ++i)
		{
			int weight = rand() % maxWeight;
			std::vector<int> coloursTemp;
			for (int i = 0; i < 6; ++i)
			{
				int temp;
				bool unique;
				do
				{
					unique = true;
					temp = rand() % colours;
					for (unsigned j = 0; j < coloursTemp.size(); ++j)
					{
						if (temp == coloursTemp.at(j))
							unique = false;
					}
					//std::cout << temp << " ";
				} while (!unique);
				coloursTemp.push_back(temp);
			}

			myfile << weight << " ";
			for (int i = 0; i < 6; ++i)
			{
				myfile << coloursTemp.at(i) << " ";
			}
			myfile << "\n";
		}
	}
	else
	{
		std::cout << std::endl << "Unable to open file";
		return false;
	}
	return true;
}
