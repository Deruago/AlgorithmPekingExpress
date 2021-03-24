#include "PekingExpress/Game/Update/GameUpdate.h"

#include <queue>
#include <climits>

PekingExpress::GameUpdate::GameUpdate(Graph* graph_, Couple* ourCouple_, std::vector<Couple*> competitors_)
	: graph(graph_),
	ourCouple(ourCouple_),
	competitors(competitors_)
{
}

PekingExpress::Couple* PekingExpress::GameUpdate::GetCompetitorById(const int id) const
{
	for (Couple* couple : competitors)
	{
		if (couple->GetId() == id)
		{
			return couple;
		}
	}

	return nullptr;
}

std::vector<PekingExpress::Couple*> PekingExpress::GameUpdate::GetAllCouples() const
{
	std::vector<Couple*> allCouples = { ourCouple };
	allCouples.insert(allCouples.end(), competitors.begin(), competitors.end());
	return allCouples;
}

const PekingExpress::Graph* PekingExpress::GameUpdate::GetGraph() const
{
	return graph;
}

void PekingExpress::GameUpdate::UpdateBudgetCompetitor(const int id, int newBudget)
{
	Couple* couple = GetCompetitorById(id);

	if (couple != nullptr)
	{
		couple->SetBudget(newBudget);
	}
}

void PekingExpress::GameUpdate::UpdateBudgetOur(int newBudget)
{
	ourCouple->SetBudget(newBudget);
}

void PekingExpress::GameUpdate::UpdateOccupiedLocations(std::vector<Node*> nodes)
{
	occupiedNodes.clear();
	occupiedNodes = nodes;
}

void PekingExpress::GameUpdate::UpdateOurLocation(const int location)
{
	for (Node* node : graph->GetLocations())
	{
		if (node->GetId() == location)
		{
			ourCouple->SetCurrentPosition(node);
		}
	}
}

#include <iostream>
using namespace std;

PekingExpress::Node* PekingExpress::GameUpdate::MinDistance(std::vector<int> dist, std::vector<bool> sptSet)
{
	int min = INT_MAX;
	Node* min_index = nullptr;

	//for (auto el : dist)
	//{
	//	cout << el << endl;
	//}

	for (Node* vec : graph->GetLocations())
	{
		if (sptSet[vec->GetId() - 1] == false && dist[vec->GetId() - 1] <= min)
		{
			min = dist[vec->GetId() - 1];
			min_index = vec;
		}
	}

	cout << min_index->GetId() << endl;

	return min_index;
}

PekingExpress::Connection* PekingExpress::GameUpdate::GetConnection(Node* startNode, Node* endNode)
{
	for (Connection con : startNode->GetConnections())
	{
		if (con.GetNode()->GetId() == endNode->GetId())
		{
			return new Connection(con.GetNode(), con.GetPrice());
		}
	}

	return nullptr;
}

bool PekingExpress::GameUpdate::IsVacantCriticalNode(Node* node)
{
	for (auto ocNode : occupiedNodes)
	{
		if (ocNode->IsCritical() && ocNode->GetId() == node->GetId())
		{
			return false;
		}
	}

	return true;
}

void PekingExpress::GameUpdate::CreatePath(std::vector<std::pair<int, Node*>> parent, int j)
{
	// Base Case : If j is source 
	if (parent[j].first == -1)
		return;

	CreatePath(parent, parent[j].first);

	cout << (parent[j].second) << " ";
}

const std::vector<PekingExpress::Node*> PekingExpress::GameUpdate::GetPath() const
{
	return path;
}

std::pair<int, PekingExpress::Node*> PekingExpress::GameUpdate::MinDistance(std::vector<int> dist, std::vector<bool> sptSet, std::vector<std::pair<int, Node*>> nodes)
{
	std::pair<int, Node*> shortestDistanceNode = { -1, nullptr } ;
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

const int PekingExpress::GameUpdate::NextMove()
{
	std::vector<int> dist;
	std::vector<bool> sptSet;

	std::vector<std::pair<int, Node*>> prev;
	std::vector<std::pair<int, Node*>> q;

	std::vector<std::pair<int, Node*>> nodes;

	for (auto node : graph->GetLocations())
	{
		dist.push_back(INT_MAX);
		sptSet.push_back(false);
		nodes.push_back({ -1, node });

		prev.push_back({ -1, nullptr });
		q.push_back({ 0, node });
	}

	for (size_t i = 0; i < graph->GetLocations().size(); i++)
	{
		nodes[i].first = i;

		q[i].first = i;
	}

	dist[0] = 0;

	for (size_t i = 0; i < graph->GetLocations().size() - 1; i++)
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

	cout << endl;

	for (auto el : dist)
	{
		cout << el << " ";
	}

	cout << endl << endl;

	for (auto el : prev)
	{
		if (!prev.empty())
			cout << el.first << " ";
	}

	cout << endl;

	CreatePath(prev, graph->GetLocations().back()->GetId());

	cout << endl;

	return 0;
}

std::pair<int, PekingExpress::Node*> PekingExpress::GameUpdate::GetVertex(std::vector<std::pair<int, Node*>> q, Connection con)
{
	std::pair<int, PekingExpress::Node*> tempNode = { -1, nullptr };

	for (auto node : q)
	{
		if (node.second == con.GetNode())
		{
			tempNode = node;
		}
	}

	return tempNode;
}

void PekingExpress::GameUpdate::ApplyOurMove(const int location)
{
	UpdateOurLocation(location);
}

PekingExpress::GameUpdate::~GameUpdate()
{
}
