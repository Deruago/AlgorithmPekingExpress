#include "PekingExpress/Game/Model/Graph.h"

PekingExpress::Graph::Graph(std::vector<Node*> locations_)
	:	locations(locations_)
{
}

PekingExpress::Graph::~Graph()
{
	for(auto* location : locations)
	{
		delete location;
	}
}

const std::vector<PekingExpress::Node*> PekingExpress::Graph::GetLocations() const
{
	return locations;
}

PekingExpress::Node* PekingExpress::Graph::GetNode(int id) const
{
	for (auto node : locations)
	{
		if (node->GetId() == id)
		{
			return node;
		}
	}

	throw std::exception{};
}

std::vector<PekingExpress::Node*> PekingExpress::Graph::GetNodes(const std::vector<int>& ids) const
{
	std::vector<Node*> nodes = {};
	for (auto id : ids)
	{
		for (auto node : locations)
		{
			if (node->GetId() == id)
			{
				nodes.push_back(node);
			}
		}
	}
	
	return nodes;
}

const std::vector<PekingExpress::Node*> PekingExpress::Graph::GetCriticalLocations() const
{
	std::vector<PekingExpress::Node*> criticals;
	for(auto* location : locations)
	{
		if (location == nullptr
			|| !location->IsCritical())
		{
			continue;
		}
		
		criticals.push_back(location);
	}

	return criticals;
}
