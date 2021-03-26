#include "PekingExpress/Game/Update/GameUpdate.h"
#include "PekingExpress/Game/Update/Algorithm.h"

#include <climits>

PekingExpress::Algorithm::Algorithm(Graph* graph_, Couple* ourCouple_) : graph(graph_), ourCouple(ourCouple_)
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

	if (ourCouple != nullptr)
	{
		int val = GetNode(ourCouple->GetCurrentPosition()).first;
		dist[val] = 0;
	}
	else
	{
		dist[0] = 0;
	}
}

std::pair<int, PekingExpress::Node*> PekingExpress::Algorithm::GetNode(PekingExpress::Node* node)
{
	std::pair<int, PekingExpress::Node*> tempNode = { -1, nullptr };

	for (auto listNode : nodes)
	{
		if (listNode.second == node)
		{
			tempNode = listNode;
		}
	}

	return tempNode;
}

int PekingExpress::Algorithm::LookForEndNode()
{
	for (auto node : nodes)
	{
		if (node.second->GetId() == 88)
		{
			return node.first;
		}
	}

	return nodes[nodes.size() - 1].first;
}

void PekingExpress::Algorithm::DoAlgorithm()
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

	std::pair<int, Node*> u = nodes[LookForEndNode()];

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

std::vector<std::pair<int, PekingExpress::Node*>> PekingExpress::Algorithm::GetPath()
{
	return path;
}
