// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSVLoader.h"
#include "DataSet.h"

#include <iostream>
#include <vector>

int main()
{
	CSVLoader csvLoader("D:\\docs\\Skryptownia\\VIII sem\\MedicalNeuralNet\\brzuch.csv");

	DataSet dataSet(std::vector<float>(10, 0), Solution(1));
	std::cout << dataSet;

	{
		std::vector<float> vec(10, 5);
		dataSet = DataSet(std::move(vec), Solution(3));

		std::cout << dataSet;
	}

	std::cout << dataSet;

	getchar();
    return 0;
}

