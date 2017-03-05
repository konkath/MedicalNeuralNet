#pragma once

#include "DataSet.h"

#include <string>

class CSVLoader
{
public:
	CSVLoader(std::string filename);

private:
	bool loadFile(std::string filename);

	DataSet getDataSet(std::string rawData);
};
