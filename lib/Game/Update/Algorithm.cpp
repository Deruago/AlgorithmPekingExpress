#include "PekingExpress/Game/Update/GameUpdate.h"
#include "PekingExpress/Game/Update/Algorithm.h"

#include <climits>

PekingExpress::Algorithm::Algorithm(Graph* graph_) : graph(graph_)
{
	for (auto node : graph->GetLocations())
	{
		dist.push_back(INT_MAX);
		sptSet.push_back(false);
		nodes.push_back({ -1, node });
		prev.push_back({ -1, nullptr });
	}

	for (size_t i = 0; i < graph->GetLocations().size(); i++)
	{
		nodes[i].first = i;
	}

	dist[0] = 0;
}

PekingExpress::Move* PekingExpress::Algorithm::DoAlgorithm()
{
	for (size_t i = 0; i < graph->GetLocations().size(); i++)
	{
		std::pair<int, Node*> u = MinDistance(dist, sptSet, nodes);

		sptSet[u.first] = true;

		for (auto neighbour : u.second->GetConnections())
		{
			std::pair<int, Node*> v = GetVertex(nodes, neighbour);

			if (!sptSet[v.first] && dist[u.first] != INT_MAX
				&& dist[u.first] + neighbour.GetPrice() < dist[v.first])
			{
				prev[v.first] = u;
				dist[v.first] = dist[u.first] + neighbour.GetPrice();
			}
		}
	}

	std::pair<int, Node*> u = nodes[graph->GetLocations().size() - 1];

	while (u.second != nullptr)
	{
		path.insert(path.begin(), u);
		u = prev[u.first];
	}
}

std::pair<int, PekingExpress::Node*> PekingExpress::Algorithm::MinDistance(std::vector<int> dist, std::vector<bool> sptSet, std::vector<std::pair<int, Node*>> nodes)
{
	std::pair<int, Node*> shortestDistanceNode = { -1, nullptr };
	int shortestDistance = INT_MAX;

	for (auto node : nodes)
	{
		if (sptSet[node.first] == false && dist[node.first] <= shortestDistance)
		{
			shortestDistance = dist[node.first];
			shortestDistanceNode = node;
		}
	}

	return shortestDistanceNode;
}

std::pair<int, PekingExpress::Node*> PekingExpress::Algorithm::GetVertex(std::vector<std::pair<int, Node*>> nodes, Connection con)
{
	std::pair<int, PekingExpress::Node*> tempNode = { -1, nullptr };

	for (auto node : nodes)
	{
		if (node.second == con.GetNode())
		{
			tempNode = node;
		}
	}

	return tempNode;
}