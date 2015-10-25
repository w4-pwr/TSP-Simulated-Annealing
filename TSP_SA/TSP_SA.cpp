// TSP_SA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include <ctime>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>


double anneal(Matrix & matrix)//wy¿arzaj 
{
	int iteration = -1;
	std::vector<int> actualOrder(matrix.getVerticles());
	double temperature = 10000.0;
	double deltaDistance = 0;
	double coolingRate = 0.9999;
	double absoluteTemperature = 0.00001;
	double shortestDistance;
	int lastSwaped =  0;
	
	for (int i = 0; i < actualOrder.size(); i++)
		actualOrder[i] = i;

	double distance = matrix.getTotalDistance(actualOrder);
	std::ofstream fout("wynik.txt");

	while (temperature > absoluteTemperature && lastSwaped<1000)
	{	

		std::vector<int> nextOrder(actualOrder);


		//losowanie zamiany
		int index1 = rand() % actualOrder.size();
		int index2 = rand() % actualOrder.size();
		int tmp = nextOrder[index1];
		nextOrder[index1] = nextOrder[index2];
		nextOrder[index2] = tmp;

		//wypisanie aktualnego stanu
		for (int i = 0; i < actualOrder.size(); i++)
			fout << actualOrder[i]<<' ';

		fout << " dystans: " << distance<<"\n";
		
		lastSwaped++;

		//obliczamy roznice odleglosci nowej sciezki
		deltaDistance = matrix.getTotalDistance(nextOrder) - distance;

		//jesli jest mniejsza
		//albo wieksza, ale i spelnia prawdpodobienstwo Boltzmana
		
		if ((deltaDistance < 0) || (distance > 0 &&
			exp(-deltaDistance / temperature) > rand()))
		{	
			//przepisujemy nowe rozwiazanie
			for (int i = 0; i < actualOrder.size(); i++)
				actualOrder[i] = nextOrder[i];
				
			distance = deltaDistance + distance;
			lastSwaped = 0;
		}

		//obnizamy "temperature"
		temperature *= coolingRate;

		iteration++;
	}
	fout.close();
	return distance;
}

int main()
{
	
	srand(time(0));
	//Matrix M("daneTSP.txt");
	Matrix M("macierzTSP.txt");//odp to 2085
	
	

	std::cout<<anneal(M);
	int a;
	std::cin >> a;
    return 0;
}

