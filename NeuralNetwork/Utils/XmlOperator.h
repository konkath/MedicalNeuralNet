#pragma once

#include "../Neuron.h"

#include <string>
#include <vector>

class XmlOperator
{
public:
	bool saveFile(const std::string fileName, std::vector<std::vector<Neuron>>& network);
	std::vector<std::vector<Neuron>> loadFile(const std::string fileName);
};
