// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSVLoader.h"
#include "TrainingData.h"

#include <iostream>
#include <vector>

int main()
{
	CSVLoader csvLoader("D:\\docs\\Skryptownia\\VIII sem\\MedicalNeuralNet\\brzuch.csv");

	for (auto i = 0; i < 2; ++i)
	{
		auto sets = TrainingData::getTrainingData().getTrainingSets();
		std::cout << sets.first.size() << std::endl << sets.second.size() << std::endl;
		std::cout << sets.first[0] << std::endl << sets.second[0] << std::endl;
	}

	getchar();
    return 0;
}

