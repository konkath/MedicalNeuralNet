#include "stdafx.h"
#include "TrainingData.h"

#include <algorithm>

TrainingData& TrainingData::getTrainingData()
{
	static TrainingData instance;
	return instance;
}

void TrainingData::populateData(std::vector<DataSet>& dataSet)
{
	data = std::move(dataSet);
}

std::pair<std::vector<DataSet>, std::vector<DataSet>> TrainingData::getTrainingSets(
	float firstSetSize, float secondSetSize)
{
	std::random_shuffle(data.begin(), data.end());

	auto middleIdx = static_cast<unsigned>((firstSetSize / (firstSetSize + secondSetSize)) * data.size());
	return std::make_pair(std::vector<DataSet>(data.begin(), data.begin() + middleIdx),
		std::vector<DataSet>(data.begin() + middleIdx + 1, data.end()));
}

const DataSet& TrainingData::operator[](const int index)
{
	return data[index];
}
