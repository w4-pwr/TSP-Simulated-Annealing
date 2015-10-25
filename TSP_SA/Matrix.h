#pragma once
#include <string>
#include <vector>

class Matrix
{
	
	int verticles;
	int edges;
	
public:
	int **M;
	Matrix();
	Matrix(std::string name);
	~Matrix();
	void cleanMatrix();
	void printMatrix();

	int getVerticles() const
	{
		return verticles;
	}

	void setVerticles(int verticles)
	{
		this->verticles = verticles;
	}

	int getEdges() const
	{
		return edges;
	}

	void setEdges(int edges)
	{
		this->edges = edges;
	}

	void readFromFile(std::string name);
	void readMatrixFromFile(std::string name);
	double getTotalDistance(std::vector<int> order);
};


