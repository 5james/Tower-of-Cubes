// Wieza N szescianow
// autor: Jakub Guzek
// ver 0.1

#pragma once

#include <cstdio>
#include <ctime>
#include <cmath>

#define NOTESTS 4
#define MINTEST 50
#define MAXTEST 500

class Table
{
private:
	int NoPrisms[NOTESTS]; // << ilosc szescianow N (przy tym ilosc kolorow i max waga tez sa rowne N)
	int Nmediana; // << Mediana wartosci przechowywanych w tablicy NoPrisms
	double Tn[NOTESTS]; // << Zmierzone czasy wykonania algorytmu
	double Qn[NOTESTS]; // << wspolczynniki Qn obliczone w trakcie dzialania programu
	double OTn[NOTESTS]; // << Oszacowana zlozonosc algorytmu

	double obliczQn(double tn, int n); // << Metoda wylicza na podstawie zadanego wzoru wspolczynnik Qn dla podanych wartosci tn oraz n
	double obliczSekundy(clock_t czas); // << Metoda, ktora zamienia cykle na czas wyrazony w ms

	Table(Table &) {}
	Table()
	{
		for (int i = 0; i < NOTESTS; ++i)
		{
			NoPrisms[i] = MINTEST + i * ((MAXTEST - MINTEST) / (NOTESTS - 1));
		}
		Nmediana = (NOTESTS >> 1);
	}
	~Table();
public:
	static Table &getInstance()
	{
		static Table pInstance;
		return pInstance;
	}


	void drawTable(); // << Metoda rysuje tabelke w konsoli
	int getNoPrisms(int n); // <<  Metoda zwraca wartosc pola NoPrisms[n]
	void setTn(int i, clock_t czas); // << Metoda rejestruje podany czas na i-tej pozycji w tablicy przechowujacej czasy wykonan
	void setQn(int i); // << Metoda ustawia wylicza oraz rejestruje na i-tej pozycji wspolczynnik Qn w tablicy przechowyjacej te wspolczynniki
	void bfs();
	void dfs();
	void random();
};

