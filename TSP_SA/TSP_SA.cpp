// TSP_SA.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include <ctime>
#include <vector>
#include <math.h>
#include <iostream>




double anneal(Matrix & matrix)//wy¿arzaj 
{
	int iteration = -1;
	std::vector<int> actualOrder(matrix.getVerticles());
	double temperature = 10000.0;
	double deltaDistance = 0;
	double coolingRate = 0.9999;
	double absoluteTemperature = 0.00001;
	double shortestDistance;

	
	for (int i = 0; i < actualOrder.size(); i++)
		actualOrder[i] = i;

	double distance = matrix.getTotalDistance(actualOrder);

	while (temperature > absoluteTemperature)
	{	

		std::vector<int> nextOrder(actualOrder);

		int index = rand() % actualOrder.size();
		int tmp = nextOrder[index];
		nextOrder[index] = nextOrder[index + 1];
		nextOrder[index + 1] = tmp;
		
		for (int i = 0; i < actualOrder.size(); i++)
			std::cout << actualOrder[i];
		std::cout << std::endl;


		deltaDistance = matrix.getTotalDistance(nextOrder) - distance;

		//if the new order has a smaller distance
		//or if the new order has a larger distance but 
		//satisfies Boltzman condition then accept the arrangement
		if ((deltaDistance < 0) || (distance > 0 &&
			exp(-deltaDistance / temperature) > rand()))
		{
			for (int i = 0; i < actualOrder.size(); i++)
				actualOrder[i] = nextOrder[i];

			distance = deltaDistance + distance;
		}

		//cool down the temperature
		temperature *= coolingRate;

		iteration++;
	}
	
	return distance;
}

int main()
{	
	srand(time(0));
	Matrix M("daneTSP.txt");
	
	

	std::cout<<anneal(M);
	
    return 0;
}

