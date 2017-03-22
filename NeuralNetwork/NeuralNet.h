#pragma once

#include "DataSet.h"
#include "Neuron.h"
#include "TrainingData.h"
#include "Enums\Solution.h"
#include "Utils\XmlOperator.h"

#include <vector>

class NeuralNet
{
public:
	NeuralNet(std::vector<unsigned> neuronLayers, float learningConstant, bool momentum,
		float momentumConstant, float activationFunction);

	Solution generateSolution(DataSet& dataSet);
	std::pair<unsigned, unsigned> generateSolution(std::vector<DataSet>& dataSets);

	void errorLearning(float acceptedError);
	void crossoverLearning(unsigned iterations);

	void saveNetwork(const std::string fileName);
	void loadNetwork(const std::string fileName);

private:
	void populateInputLayer(DataSet& dataSet);
	void calculateLayer(unsigned index);
	Solution getBestOutput();

	float learnNetwork(std::vector<DataSet>& learningData);
	std::vector<float> learnOutputLayer(Solution solution, std::vector<std::vector<Neuron>>& oldNetwork,
		std::vector<std::vector<Neuron>>& newNetwork, float& networkError);
	std::vector<float> learnHiddenLayer(unsigned layerIdx, std::vector<float>& errors,
		std::vector<std::vector<Neuron>>& oldNetwork, std::vector<std::vector<Neuron>>& newNetwork);

	void calculateWeights(std::vector<Neuron>& oldLayer, std::vector<Neuron>& layer,
		std::vector<float> errors, unsigned weightIdx);

	float networkError;
	float learningConstant;
	float momentumConstant;
	float activationFunction;
	bool momentum;
	std::vector<std::vector<Neuron>> neurons;

	XmlOperator xml;
	TrainingData& trainingData;
};
