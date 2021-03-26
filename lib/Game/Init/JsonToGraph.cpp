#include "PekingExpress/Game/Init/JsonToGraph.h"
#include "PekingExpress/Game/Init/GraphBuilder.h"
#include <iostream>

PekingExpress::Graph* PekingExpress::JsonToGraph::ConvertJsonToGraph(const std::string& json)
{
	GraphBuilder graphBuilder;
	
	Json::Value value;
	reader.parse(json, value);

	for (const auto& critical_node : value["locations"]["critical"])
	{
		graphBuilder.AddCriticalNode(critical_node.asInt());
	}

	auto connections = value["connections"];
	for (auto i = 0; i < connections["source"].size(); i++)
	{
		auto source = connections["source"][i];
		auto target = connections["target"][i];
		auto price = connections["price"][i];
		
		graphBuilder.AddNode(source.asInt());
		graphBuilder.AddNode(target.asInt());

		graphBuilder.AddConnection(source.asInt(), target.asInt(), price.asInt());
	}

	return graphBuilder.GetGraph();
}
