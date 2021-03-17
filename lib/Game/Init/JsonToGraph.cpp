#include "PekingExpress/Game/Init/JsonToGraph.h"
#include "PekingExpress/Game/Init/GraphBuilder.h"
#include <iostream>

PekingExpress::Graph* PekingExpress::JsonToGraph::ConvertJsonToGraph(const std::string& json)
{
	GraphBuilder graphBuilder;
	
	Json::Value value;
	reader.parse(json, value);

	std::cout << value << std::endl;
	std::cout << value["locations"] << std::endl;

	for (const auto& critical_node : value["locations"]["critical"])
	{
		std::cout << "Add critical: " << critical_node.asInt() << std::endl;
		graphBuilder.AddCriticalNode(critical_node.asInt());
	}

	auto connections = value["connections"];
	for (auto i = 0; i < connections["source"].size(); i++)
	{
		auto source = connections["source"][i];
		auto target = connections["target"][i];
		auto price = connections["price"][i];
		
		std::cout << "Add node: " << source.asInt() << std::endl;
		std::cout << "Add node: " << target.asInt() << std::endl;
		std::cout << "Add Connection, Source: " << source.asInt() << " Target: " << target.asInt() << " Price: " << price.asInt() << std::endl;
		
		graphBuilder.AddNode(source.asInt());
		graphBuilder.AddNode(target.asInt());

		graphBuilder.AddConnection(source.asInt(), target.asInt(), price.asInt());
	}

	return graphBuilder.GetGraph();
}
