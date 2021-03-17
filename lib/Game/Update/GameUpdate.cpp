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

	for (auto vec : graph->GetLocations())
	{
		if (sptSet[vec->GetId() - 1] == false && dist[vec->GetId() - 1] <= min)
		{
			min = dist[vec->GetId() - 1];
			min_index = vec;
		}
	}

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

void PekingExpress::GameUpdate::printPath(Node* parent[], int j)
{
	// Base Case : If j is source 
	if (parent[j - 1]->GetId() == -1)
		return;

	printPath(parent, parent[j - 1]->GetId());

	printf("%d ", j);
}


const int PekingExpress::GameUpdate::NextMove()
{
	std::vector<int> dist(graph->GetLocations().size(), INT_MAX);
	std::vector<bool> sptSet(graph->GetLocations().size(), false);
	std::vector<Node*> parent(graph->GetLocations().size(), new Node(-1, {}, false));

	dist[ourCouple->GetCurrentPosition()->GetId() - 1] = 0;

	for (int i = 0; i < graph->GetLocations().size() - 1; i++)
	{
		Node* u = MinDistance(dist, sptSet);

		if (u == nullptr)
		{
			return -1;
		}

		sptSet[u->GetId() - 1] = true;

		for (auto vec : graph->GetLocations())
		{
			Connection* tempCon = GetConnection(u, vec);

			if (!sptSet[vec->GetId() - 1] && tempCon != nullptr && dist[u->GetId() - 1] && dist[u->GetId() - 1] + tempCon->GetPrice() < dist[vec->GetId() - 1])
			{
				parent[vec->GetId() - 1] = u;
				dist[vec->GetId() - 1] = dist[u->GetId() - 1] + tempCon->GetPrice();
			}
		}
	}

	printPath(parent.data(), graph->GetLocations().back()->GetId());

	//for (auto node : dist)
	//{
	//	cout << node << endl;
	//}

	return parent[0]->GetId();
}

void PekingExpress::GameUpdate::ApplyOurMove(const int location)
{
	UpdateOurLocation(location);
}

PekingExpress::GameUpdate::~GameUpdate()
{
}
