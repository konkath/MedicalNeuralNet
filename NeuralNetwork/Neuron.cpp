#include "stdafx.h"
#include "Neuron.h"
#include "Utils/RandomGenerator.h"

Neuron::Neuron(unsigned nOfConnections) : weights(nOfConnections)
{
	initializeRandomWeights();
}

Neuron::Neuron(std::vector<float> weights) : weights(weights)
{

}

void Neuron::initializeRandomWeights()
{
	auto& generator(RandomGenerator<float>::getGenerator());

	for (auto& weight : weights)
	{
		weight = generator.getRandom(-0.3f, 0.3f);
	}
}

float Neuron::getValue()
{
	return value;
}

void Neuron::setValue(float v)
{
	value = v;
}

float& Neuron::operator[](const int index)
{
	return weights[index];
}

unsigned Neuron::size()
{
	return weights.size();
}