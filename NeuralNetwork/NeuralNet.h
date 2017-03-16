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
	void learnNetwork(std::vector<DataSet>& learningData);

private:
	void populateInputLayer(DataSet& dataSet);
	void calculateLayer(unsigned index);
	Solution getBestOutput();

	std::vector<float> learnOutputLayer(Solution solution, std::vector<std::vector<Neuron>>& newNetwork);
	std::vector<float> learnHiddenLayer(unsigned layerIdx, std::vector<float>& errors,
		std::vector<std::vector<Neuron>>& newNetwork);

	float networkError;
	float acceptedError;
	
	float learningConstant;
	float activationFunction;
	bool momentum;
	std::vector<std::vector<Neuron>> neurons;
};
