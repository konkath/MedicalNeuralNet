// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CSVLoader.h"
#include "TrainingData.h"
#include "NeuralNet.h"

#include <iostream>
#include <vector>

int main()
{
	CSVLoader csvLoader("D:\\docs\\Skryptownia\\VIII sem\\MedicalNeuralNet\\brzuch.csv");
	auto& trainingData(TrainingData::getTrainingData());

	auto set = trainingData.getTrainingSets();

	std::vector<unsigned> networkLayers = { 31, 30, 8 };

	auto network(NeuralNet(networkLayers, 0.25, false, 0.5));

	auto good = 0, bad = 0;
	for (auto& test : set.first)
	{
		if (test.getSolution() == network.generateSolution(test))
		{
			good++;
		}
		else
		{
			bad++;
		}
	}

	for (auto& test : set.second)
	{
		if (test.getSolution() == network.generateSolution(test))
		{
			good++;
		}
		else
		{
			bad++;
		}
	}

	std::cout << "Good guesses " << good << std::endl << "Poor guesses " << bad << std::endl;

	getchar();
	////////////////////////////////////////////////////////////////////////////////////

	for (auto i = 0; i < 2; ++i)
	{
		auto sets = trainingData.getTrainingSets();
		std::cout << sets.first.size() << std::endl << sets.second.size() << std::endl;
		std::cout << sets.first[0] << std::endl << sets.second[0] << std::endl;
	}

	getchar();
    return 0;
}

