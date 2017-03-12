#pragma once

#include "Enums\Solution.h"

#include <vector>

enum Solutions
{

};

class DataSet
{
public:
	DataSet(std::vector<float>& trainingData, Solution solution);

	Solution getSolution();

	const float operator[](const int index);
	friend std::ostream& operator<<(std::ostream& os, const DataSet& dataSet);

private:
	Solution solution;
	std::vector<float> data;
};
