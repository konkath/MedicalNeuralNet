#pragma once

#include "DataSet.h"

#include <vector>

class TrainingData
{
public:
	TrainingData(TrainingData const&) = delete;
	void operator=(TrainingData const&) = delete;
	static TrainingData& getTrainingData(); 

	void populateData(std::vector<DataSet>& dataSet);
	std::pair<std::vector<DataSet>, std::vector<DataSet>> getTrainingSets(
		float firstSetSize = .5f, float secondSetSize = .5f);

	const DataSet& operator[](const int index);

private:
	TrainingData() {}

	std::vector<DataSet> data;
};
