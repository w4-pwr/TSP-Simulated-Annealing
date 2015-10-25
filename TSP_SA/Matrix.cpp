#include "stdafx.h"
#include "Matrix.h"
#include <fstream>
#include <vector>
#include <iostream>


Matrix::Matrix(std::string name)
{
	//readFromFile(name);
	readMatrixFromFile(name);
}
	

Matrix::~Matrix()
{
	for (int i = 0; i < getVerticles()	; i++)
		delete[] M[i];
	delete[] M;
}


void Matrix::cleanMatrix()
{
	for (int i = 0; i < getVerticles(); i++)
		for (int j = 0; j < getVerticles(); j++)
			M[i][j] = 0;
}

void Matrix::printMatrix()
{
	for (int i = 0; i < getVerticles(); i++)
	{
		for (int j = 0; j < getVerticles(); j++)
		{
			std::cout << M[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

void Matrix::readFromFile(std::string name)
{
	//otworz plik
	std::ifstream fin;
	fin.open(name.c_str());
	if (!fin.is_open()) {
		throw "Brak pliku z danymi";
	}
	fin >> verticles;
	std::cout << verticles;
	edges = ((getVerticles() * (getVerticles() - 1)) / 2);

	M = new int*[getVerticles()];
	for (int i = 0; i < getVerticles(); i++)
		M[i] = new int[getVerticles()];

	cleanMatrix();

	int start, end, weight;
	for (int i = 0; i < getEdges()	; i++) {
		fin >> start;
		fin >> end;
		fin >> weight;

		M[start][end] = weight;
		M[end][start] = weight;
	}
	fin.close();

	printMatrix();
}

void Matrix::readMatrixFromFile(std::string name)
{
	//otworz plik
	std::ifstream fin;
	fin.open(name.c_str());
	if (!fin.is_open()) {
		throw "Brak pliku z danymi";
	}
	fin >> verticles;
	std::cout << verticles;
	edges = ((getVerticles() * (getVerticles() - 1)) / 2);

	M = new int*[getVerticles()];
	for (int i = 0; i < getVerticles(); i++)
		M[i] = new int[getVerticles()];

	cleanMatrix();

	for (int i = 0; i < getVerticles(); i++)
	{
		for (int j = 0; j < getVerticles(); j++)
		{
			fin >> M[i][j];
		}
	}
	fin.close();

	printMatrix();
}
double Matrix::getTotalDistance(std::vector<int> order)
{
	double sum = 0;;
	for (int i = 0; i < order.size() - 1; i++)
	{
		sum += M[order[i]][order[i + 1]];
	}
	sum += M[order[0]][order[order.size()-1]];
	return sum;
}
