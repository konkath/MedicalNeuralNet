#pragma once

#include <vector>

class Neuron
{
public:
	Neuron(unsigned nOfConnections);
	Neuron(std::vector<float> weights);

	float getValue();
	void setValue(float v);

	float& operator[](const int index);
	unsigned size();

private:
	void initializeRandomWeights();

	float value;
	std::vector<float> weights;
};
