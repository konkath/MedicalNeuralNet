#include "stdafx.h"
#include "NeuralNet.h"

NeuralNet::NeuralNet(std::vector<unsigned> neuronLayers, float learningConstant, bool momentum,
	float activationFunction) : learningConstant(learningConstant), momentum(momentum),
	activationFunction(activationFunction)
{
	for (auto it = neuronLayers.begin(); it != neuronLayers.end() - 1; ++it)
	{
		neurons.push_back(std::vector<Neuron>(*(it), Neuron(*(it + 1))));
	}
	neurons.push_back(std::vector<Neuron>(*(neuronLayers.end() - 1), Neuron(0)));
}

Solution NeuralNet::generateSolution(DataSet& dataSet)
{
	populateInputLayer(dataSet);

	for (auto idx = 1; idx < neurons.size(); ++idx)
	{
		calculateLayer(idx);
	}

	return getBestOutput();
}

void NeuralNet::populateInputLayer(DataSet& dataSet)
{
	for (auto idx = 0u; idx < neurons[0].size(); ++idx)
	{
		neurons[0][idx].setValue(dataSet[idx]);
	}
}

void NeuralNet::calculateLayer(unsigned index)
{
	for (auto neuronIdx = 0; neuronIdx < neurons[index].size(); ++neuronIdx)
	{
		auto& neuron = neurons[index][neuronIdx];
		float valueSum = 0;

		for (auto& prevNeuron : neurons[index - 1])
		{
			valueSum += prevNeuron.getValue() * prevNeuron[neuronIdx] / exp(-1 * activationFunction);
		}
		neuron.setValue(valueSum);
	}
}

Solution NeuralNet::getBestOutput()
{
	auto lastLayer = neurons.size() - 1;
	std::pair<int, float> bestSolution = std::make_pair(0, neurons[lastLayer][0].getValue());

	for (auto idx = 1; idx < neurons[lastLayer].size(); ++idx)
	{
		auto value = neurons[lastLayer][idx].getValue();
		if (value > bestSolution.second)
		{
			bestSolution = std::make_pair(idx, value);
		}
	}

	return Solution(bestSolution.first);
}
