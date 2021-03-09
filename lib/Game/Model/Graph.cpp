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
