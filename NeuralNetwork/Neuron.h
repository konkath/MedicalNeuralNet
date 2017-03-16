#pragma once

#include <vector>

class Neuron
{
public:
	Neuron(unsigned nOfConnections);

	float getValue();
	void setValue(float v);

	float& operator[](const int index);

private:
	void initializeRandomWeights();

	float value;
	std::vector<float> weights;
};
