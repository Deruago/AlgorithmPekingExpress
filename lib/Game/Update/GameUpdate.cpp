#include "PekingExpress/Game/Update/GameUpdate.h"
#include "PekingExpress/Game/Update/Algorithm.h"

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

#include <iostream>

bool PekingExpress::GameUpdate::IsOccupiedCriticalNode(Node* node)
{
	if (node == nullptr)
	{
		return false;
	}

	for (auto ocNode : occupiedNodes)
	{
		if (ocNode->GetId() == node->GetId() && ocNode->IsCritical())
		{
			return true;
		}
	}

	return false;
}

const std::vector<std::pair<int, PekingExpress::Node*>> PekingExpress::GameUpdate::GetPath() const
{
	return path;
}

void PekingExpress::GameUpdate::SetTargetNode(Node* targetNode_)
{
	targetNode = targetNode_;
}

PekingExpress::Node* PekingExpress::GameUpdate::GetNextNodeInPath()
{
	for (size_t i = 0; i < path.size()-1; i++)
	{
		if (path[i].second == ourCouple->GetCurrentPosition())
		{
			if (path[i + 1].second != nullptr)
			{
				return path[i + 1].second;
			}
			else
			{
				return path[i].second;
			}
		}
	}

	return nullptr;
}

PekingExpress::Connection* PekingExpress::GameUpdate::GetConnection(Node* startNode, Node* endNode)
{
	if (startNode == nullptr || endNode == nullptr)
	{
		return nullptr;
	}

	for (Connection con : startNode->GetConnections())
	{
		if (con.GetNode() == endNode)
		{
			return new Connection(con.GetNode(), con.GetPrice());
		}
	}

	return nullptr;
}

PekingExpress::Move* PekingExpress::GameUpdate::NextMove()
{
	if (path.empty())
	{
		Algorithm algorithm = Algorithm(graph, ourCouple);
		algorithm.DoAlgorithm();
		path = algorithm.path;
	}

	for (auto node : path)
	{
		std::cout << node.second->GetId() << std::endl;
	}

	Node* startNode = ourCouple->GetCurrentPosition();
	Node* endNode = GetNextNodeInPath();

	if (IsOccupiedCriticalNode(endNode))
	{
		return new Move(startNode, startNode, 0);
	}

	int price = 0;
	Connection* con = GetConnection(startNode, endNode);
	if (con != nullptr)
	{
		int price = con->GetPrice();
		delete con;
	}

	return new Move(startNode, endNode, price);
}

void PekingExpress::GameUpdate::ApplyOurMove(const Move* location)
{
	UpdateOurLocation(location);
	UpdateBudgetOur(ourCouple->GetBudget() - location->GetPrice());
}
