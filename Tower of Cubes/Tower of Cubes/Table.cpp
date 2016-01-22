// Wieza N szescianow
// autor: Jakub Guzek
// ver 0.1

#include "Table.h"

double Table::obliczQn(double tn, int n)
{
	return ((Tn[n] * OTn[Nmediana]) / ((OTn[n]) * Tn[Nmediana]));
}

void Table::drawTable()
{
	printf("|    n    |   t(n)  |   q(n)   |\n");
	printf("--------------------------------\n");
	for (int i = 0; i < NOTESTS; ++i)
	{
		printf("|%09d|%09d|%01.8f|\n", NoPrisms[i], (unsigned int)Tn[i], Qn[i]);
	}
	printf("--------------------------------\n");
}

int Table::getNoPrisms(int n)
{
	return NoPrisms[n];
}

void Table::setTn(int i, clock_t czas)
{
	Tn[i] = obliczSekundy(czas);
}

void Table::setQn(int i)
{
	Qn[i] = obliczQn(Tn[i], i);
}

void Table::bfs()
{
	for (int i = 0; i < NOTESTS; ++i)
		OTn[i] = NoPrisms[i] * NoPrisms[i] * log2(NoPrisms[i]);
}

void Table::dfs()
{
	for (int i = 0; i < NOTESTS; ++i)
		OTn[i] = NoPrisms[i] * NoPrisms[i] * log2(NoPrisms[i]) * log2(NoPrisms[i]) + 2 * NoPrisms[i] * NoPrisms[i];
}

void Table::random()
{
	for (int i = 0; i < NOTESTS; ++i)
		OTn[i] = NoPrisms[i] * log2(NoPrisms[i]);
}

double Table::obliczSekundy(clock_t czas)
{
	double result = static_cast <double>(czas) / (CLOCKS_PER_SEC)* 1000;
	if (result == 0.0)
		result = 1.0;
	return result;
}



Table::~Table()
{
}
