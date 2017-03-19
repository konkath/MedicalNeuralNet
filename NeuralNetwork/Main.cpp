// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Utils/CSVLoader.h"
#include "TrainingData.h"
#include "NeuralNet.h"

#include <iostream>
#include <vector>

int main()
{
	CSVLoader csvLoader("D:\\docs\\Skryptownia\\VIII sem\\MedicalNeuralNet\\brzuch.csv");

	std::vector<unsigned> networkLayers = { 31, 62, 8 };
	auto network1(NeuralNet(networkLayers, 0.5, false, 0.5));

	std::cout << "Error learning:" << std::endl;
	network1.errorLearning(0.0015f);

	////////////////////////////////////////////////////////////////////////////////////

	auto network2(NeuralNet(networkLayers, 0.5, false, 0.5));
	
	std::cout << "Crossover learning:" << std::endl;
	network2.crossoverLearning(5);

	getchar();
	////////////////////////////////////////////////////////////////////////////////////

	auto& trainingData(TrainingData::getTrainingData());
	auto set = trainingData.getTrainingSets();
	std::cout << to_string(network1.generateSolution(set.first[0])) << std::endl;

	std::cout << "XML test:" << std::endl;
	network1.saveNetwork("test.xml");
	network1.loadNetwork("test.xml");

	std::cout << to_string(network1.generateSolution(set.first[0])) << std::endl;

	getchar();
	////////////////////////////////////////////////////////////////////////////////////

	std::cout << "DataSet test:" << std::endl;
	for (auto i = 0; i < 2; ++i)
	{
		auto sets = trainingData.getTrainingSets();
		std::cout << sets.first.size() << std::endl << sets.second.size() << std::endl;
		std::cout << sets.first[0] << std::endl << sets.second[0] << std::endl;
	}

	getchar();
    return 0;
}
