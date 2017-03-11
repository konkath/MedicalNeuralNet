#include "stdafx.h"
#include "Neuron.h"
#include "RandomGenerator.h"

Neuron::Neuron(unsigned nOfConnections) : weights(nOfConnections)
{
	initializeRandomWeights();
}

void Neuron::initializeRandomWeights()
{
	auto& generator(RandomGenerator<float>::getGenerator());

	for (auto& weight : weights)
	{
		weight = generator.getRandom(-0.3, 0.3);
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

float Neuron::operator[](const int index)
{
	return weights[index];
}

