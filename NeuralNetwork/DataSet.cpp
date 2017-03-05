#include "stdafx.h"
#include "DataSet.h"

#include <iostream>

DataSet::DataSet(std::vector<float>& trainingData, Solution solution)
	: data(trainingData), solution(solution)
{
}

short DataSet::getSolution()
{
	return solution;
}

const float DataSet::operator[](const int index)
{
	return data[index];
}

std::ostream & operator<<(std::ostream & os, const DataSet & dataSet)
{
	os << "Data: " << std::endl;
	for (const auto& d : dataSet.data)
	{
		os << d << ", ";
	}
	os << std::endl << "With solution: " << to_string(dataSet.solution) << std::endl;

	return os;
}
