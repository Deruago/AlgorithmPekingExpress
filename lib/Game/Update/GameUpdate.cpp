#include "PekingExpress/Game/Update/GameUpdate.h"
#include "PekingExpress/Game/Update/Algorithm.h"
#include <iostream>

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

void PekingExpress::GameUpdate::UpdateBudgetOur(int newBudget)
{
	ourCouple->SetBudget(newBudget);
}

void PekingExpress::GameUpdate::UpdateOccupiedLocations(std::vector<Node*> nodes)
{
	occupiedNodes.clear();
	occupiedNodes = nodes;
}

void PekingExpress::GameUpdate::UpdateOurLocation(const Move* location)
{
	for (Node* node : graph->GetLocations())
	{
		if (node == location->GetEndLocation())
		{
			ourCouple->SetCurrentPosition(node);
		}
	}
}

PekingExpress::Connection* PekingExpress::GameUpdate::GetConnection(Node* startNode, Node* endNode)
{
	for (Connection con : startNode->GetConnections())
	{
		if (con.GetNode()->GetId() == endNode->GetId())
		{
			std::cout << "Found " << std::endl;
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

const std::vector<std::pair<int, PekingExpress::Node*>> PekingExpress::GameUpdate::GetPath() const
{
	return path;
}

PekingExpress::Node* PekingExpress::GameUpdate::GetNextNodeInPath()
{
	for (auto node : path)
	{
		if (node.second == ourCouple->GetCurrentPosition())
		{
			return path[node.first + 1].second;
		}
	}

	return nullptr;
}

PekingExpress::Move* PekingExpress::GameUpdate::NextMove()
{
	// Generates path from start position to desired goal
	// optimised for price. Not speed
	Algorithm algorithm = Algorithm(graph, ourCouple);
	algorithm.DoAlgorithm();
	path = algorithm.path;
	for (auto node : path)
	{
		std::cout << node.second->GetId() << " ";
	}
	std::cout << '\n';

	Node* startNode = ourCouple->GetCurrentPosition();
	Node* endNode = GetNextNodeInPath();

	if (!IsVacantCriticalNode(endNode))
	{
		return new Move(startNode, startNode, 0);
	}

	Connection* con = GetConnection(startNode, endNode);
	int price = con->GetPrice();
	delete con;

	return new Move(startNode, endNode, price);
}

void PekingExpress::GameUpdate::ApplyOurMove(const Move* location)
{
	UpdateOurLocation(location);
	UpdateBudgetOur(ourCouple->GetBudget() - location->GetPrice());
}
