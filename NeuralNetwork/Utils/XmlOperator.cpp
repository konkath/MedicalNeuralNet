#include "stdafx.h"

#include "XmlOperator.h"
#include "../rapidXml/rapidxml.hpp"
#include "../rapidXml/rapidxml_print.hpp"
#include "../rapidXml/rapidxml_utils.hpp"

#include <fstream>
#include <iostream>

bool XmlOperator::saveFile(const std::string fileName, std::vector<std::vector<Neuron>>& network)
{
	rapidxml::xml_document<> doc;
	auto declaration = doc.allocate_node(rapidxml::node_declaration);
	declaration->append_attribute(doc.allocate_attribute("version", "1.0"));
	declaration->append_attribute(doc.allocate_attribute("encoding", "utf-8"));
	declaration->append_attribute(doc.allocate_attribute("standalone", "no"));
	doc.append_node(declaration);

	auto net = doc.allocate_node(rapidxml::node_element, "NeuralNetwork");
	net->append_node(doc.allocate_node(rapidxml::node_element,
		"source", "https://github.com/konkath/MedicalNeuralNet"));

	auto networkLayers = doc.allocate_node(rapidxml::node_element, "NetworkLayers");
	for (auto& layer : network)
	{
		auto networkLayer = doc.allocate_node(rapidxml::node_element, "Layer");
		for (auto& neuron : layer)
		{
			auto networkNeuron = doc.allocate_node(rapidxml::node_element, "Neuron");
			for (auto i = 0u; i < neuron.size(); ++i)
			{
				auto networkWeight = doc.allocate_node(rapidxml::node_element, "Weight",
					doc.allocate_string(std::to_string(neuron[i]).c_str()));
				networkNeuron->append_node(networkWeight);
			}
			networkLayer->append_node(networkNeuron);
		}
		networkLayers->append_node(networkLayer);
	}

	net->append_node(networkLayers);
	doc.append_node(net);

	std::ofstream file;
	file.open(fileName, std::fstream::in | std::fstream::trunc);
	file << doc;

	file.close();
	doc.clear();

	return true;
}

std::vector<std::vector<Neuron>> XmlOperator::loadFile(const std::string fileName)
{
	std::vector<std::vector<Neuron>> neuralNetwork;

	rapidxml::file<> xmlFile(fileName.c_str());
	rapidxml::xml_document<> doc;

	try
	{
		doc.parse<0>(xmlFile.data());

		auto networkLayers = doc.first_node()->last_node();
		for (auto layer = networkLayers->first_node(); layer; layer = layer->next_sibling())
		{
			std::vector<Neuron> neurons;
			for (auto neuron = layer->first_node(); neuron; neuron = neuron->next_sibling())
			{
				std::vector<float> weights;
				for (auto weight = neuron->first_node(); weight; weight = weight->next_sibling())
				{
					weights.emplace_back(std::stof(weight->value()));
				}
				neurons.emplace_back(weights);
			}
			neuralNetwork.emplace_back(neurons);
		}

		doc.clear();
	}
	catch (rapidxml::parse_error p)
	{
		std::cout << "Loading failed with error: " << p.what() << std::endl;
		return std::vector<std::vector<Neuron>>();
	}

	return std::move(neuralNetwork);
}
