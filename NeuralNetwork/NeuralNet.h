#pragma once

#include "DataSet.h"
#include "Neuron.h"
#include "Enums\Solution.h"

#include <vector>

class NeuralNet
{
public:
	NeuralNet(std::vector<unsigned> neuronLayers, float learningConstant, bool momentum,
		float activationFunction);

	Solution generateSolution(DataSet& dataSet);

private:
	void populateInputLayer(DataSet& dataSet);
	void calculateLayer(unsigned index);
	Solution getBestOutput();

	float learningConstant;
	float activationFunction;
	bool momentum;
	std::vector<std::vector<Neuron>> neurons;
};
