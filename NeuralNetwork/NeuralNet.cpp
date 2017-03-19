#include "stdafx.h"
#include "NeuralNet.h"

#include <algorithm>
#include <iostream>

NeuralNet::NeuralNet(std::vector<unsigned> neuronLayers, float learningConstant, bool momentum,
	float activationFunction) : learningConstant(learningConstant), momentum(momentum),
	activationFunction(activationFunction), networkError(FLT_MAX), trainingData(TrainingData::getTrainingData())
{
	for (auto it = neuronLayers.begin(); it != neuronLayers.end(); ++it)
	{
		neurons.push_back(std::vector<Neuron>());

		auto currentLayer = neurons.size() - 1;
		neurons[currentLayer].reserve(*it);

		auto nOfWeights = it != neuronLayers.end() - 1 ? *(it + 1) : 0;
		for (auto idx = 0u; idx < *it; ++idx)
		{
			neurons[currentLayer].emplace_back(Neuron(nOfWeights));
		}
	}
}

Solution NeuralNet::generateSolution(DataSet& dataSet)
{
	populateInputLayer(dataSet);

	for (auto idx = 1u; idx < neurons.size(); ++idx)
	{
		calculateLayer(idx);
	}

	return getBestOutput();
}

std::pair<unsigned, unsigned> NeuralNet::generateSolution(std::vector<DataSet>& dataSets)
{
	auto correct = 0, wrong = 0;
	for (auto& set : dataSets)
	{
		auto solution = generateSolution(set);
		solution == set.getSolution() ? correct++ : wrong++;
	}

	return std::make_pair(correct, wrong);
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
	for (auto neuronIdx = 0u; neuronIdx < neurons[index].size(); ++neuronIdx)
	{
		auto& neuron = neurons[index][neuronIdx];
		float valueSum = 0;

		for (auto& prevNeuron : neurons[index - 1])
		{
			valueSum += prevNeuron.getValue() * prevNeuron[neuronIdx];
		}
		neuron.setValue(1 / (1 + exp(-1 * activationFunction * valueSum)));
	}
}

Solution NeuralNet::getBestOutput()
{
	auto lastLayer = neurons.size() - 1;
	std::pair<int, float> bestSolution = std::make_pair(0, neurons[lastLayer][0].getValue());

	for (auto idx = 1u; idx < neurons[lastLayer].size(); ++idx)
	{
		auto value = neurons[lastLayer][idx].getValue();
		if (value > bestSolution.second)
		{
			bestSolution = std::make_pair(idx, value);
		}
	}

	return Solution(bestSolution.first);
}

void NeuralNet::errorLearning(float acceptedError)
{
	auto avgNetworkError = .0f;
	auto sets = trainingData.getTrainingSets(.85f, .15f);

	do
	{
		auto networkError = learnNetwork(sets.first);
		avgNetworkError = networkError / (sets.first.size() + sets.second.size());

		std::random_shuffle(sets.first.begin(), sets.first.end());
	} while (acceptedError < avgNetworkError);

	auto solutions = generateSolution(sets.second);
	std::cout << "Learning finished with acceptedError:" << avgNetworkError << std::endl << 
		"Unused data correct/wrong ratio: " << solutions.first << "/" << solutions.second << std::endl;
}

void NeuralNet::crossoverLearning(unsigned iterations)
{
	for (auto i = 0u; i < iterations; ++i)
	{
		auto sets = trainingData.getTrainingSets();
		learnNetwork(sets.first);

		auto solutions = generateSolution(sets.second);
		std::cout << "Iteration: " << i << ", ratio: " << solutions.first << "/" << solutions.second << std::endl;
	}
}

float NeuralNet::learnNetwork(std::vector<DataSet>& learningData)
{
	auto networkError = .0f;

	for (auto& data : learningData)
	{	
		generateSolution(data);

		std::vector<std::vector<Neuron>> newNetwork(neurons);
		auto errors = learnOutputLayer(data.getSolution(), newNetwork, networkError);

		// output and input layer are ignored here
		for (auto layerIdx = neurons.size() - 2; layerIdx > 0; --layerIdx)
		{
			errors = learnHiddenLayer(layerIdx, errors, newNetwork);
		}
		neurons = newNetwork;
	}

	return networkError;
}

std::vector<float> NeuralNet::learnOutputLayer(Solution solution, 
	std::vector<std::vector<Neuron>>& newNetwork, float& networkError)
{
	auto outputLayer = neurons.size() - 1, nOfOutputNeurons = neurons[outputLayer].size();
	std::vector<float> errors(nOfOutputNeurons);

	for (auto idx = 0u; idx < nOfOutputNeurons; ++idx)
	{
		auto neuronValue = neurons[outputLayer][idx].getValue();
		auto result = solution != idx ? 0 : 1;

		networkError += static_cast<float>(0.5 * pow(neuronValue - result, 2));  // singleError
		errors[idx] = neuronValue * (1 - neuronValue) * -(result - neuronValue);  // current neuron error

		for (auto& prevNeuron : newNetwork[outputLayer - 1])
		{
			prevNeuron[idx] -= errors[idx] * prevNeuron.getValue() * learningConstant;  // weight modification
		}
	}

	return errors;
}

// delta w = q (learning constant) * d (propagated error) * z (neuron value)
std::vector<float> NeuralNet::learnHiddenLayer(unsigned layerIdx, 
	std::vector<float>& errors, std::vector<std::vector<Neuron>>& newNetwork)
{
	auto layerSize = neurons[layerIdx].size(), errorsSize = errors.size();
	std::vector<float> layerErrors(layerSize);

	auto errorSum = .0;
	for (auto neuronIdx = 0u; neuronIdx < layerSize; ++neuronIdx)
	{
		for (auto errorIdx = 0u; errorIdx < errorsSize; ++errorIdx)
		{
			errorSum += errors[errorIdx] * neurons[layerIdx][neuronIdx][errorIdx];  // single error
		}

		auto neuronValue = neurons[layerIdx][neuronIdx].getValue();
		layerErrors[neuronIdx] = static_cast<float>(errorSum * neuronValue * (1 - neuronValue));  //current neuron error
		
		for (auto& prevNeuron : newNetwork[layerIdx - 1])
		{
			prevNeuron[neuronIdx] -= layerErrors[neuronIdx] * prevNeuron.getValue() * learningConstant;  // weight modification
		}
	}

	return layerErrors;
}

void NeuralNet::saveNetwork(const std::string fileName)
{
	xml.saveFile(fileName, neurons);
}

void NeuralNet::loadNetwork(const std::string fileName)
{
	neurons = xml.loadFile(fileName);
}
