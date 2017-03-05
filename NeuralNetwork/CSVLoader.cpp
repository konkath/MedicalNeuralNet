#include "stdafx.h"
#include "CSVLoader.h"

#include <iostream>
#include <fstream>
#include <vector>

CSVLoader::CSVLoader(std::string filename)
{
	loadFile(filename);
}

bool CSVLoader::loadFile(std::string filename)
{
	std::fstream file;
	file.open(filename, std::ios::in);

	if (file.good())
	{
		std::vector<DataSet> data;

		std::string rawData;
		while (!file.eof())
		{
			file >> rawData;
			auto dupa = getDataSet(rawData);
			std::cout << dupa;

			data.push_back(getDataSet(rawData));
		}

		// insert data into TrainingData class
	}
	else
	{
		return false;
	}
	
	file.close();
	return true;
}

DataSet CSVLoader::getDataSet(std::string rawData)
{
	std::vector<float> data;
	std::string singleItem = "";

	for (const auto c : rawData)
	{
		if (c != ';')
		{
			singleItem += c;
		}
		else
		{
			data.push_back(atof(singleItem.c_str()));
			singleItem = "";
		}
	}
	auto solution = atoi(singleItem.c_str());

	return DataSet(data, Solution(solution));
}