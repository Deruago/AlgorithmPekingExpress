#include "PekingExpress/Game/Update/GameUpdate.h"

#include <queue>

#define OFFSET 1

PekingExpress::GameUpdate::GameUpdate(IGraph* graph_, ICouple* ourCouple_, std::vector<ICouple*> competitors_) 
	: graph(graph_),
	  ourCouple(ourCouple_),
	  competitors(competitors_)
{
}

PekingExpress::ICouple* PekingExpress::GameUpdate::GetCompetitorById(const int id) const
{
	for (ICouple* couple : competitors)
	{
		if (couple->GetId() == id)
		{
			return couple;
		}
	}

	return nullptr;
}

std::vector<PekingExpress::ICouple*> PekingExpress::GameUpdate::GetAllCouples()
{
	competitors.insert(competitors.begin(), ourCouple);
	return competitors;
}

PekingExpress::IGraph* PekingExpress::GameUpdate::GetGraph()
{
	return graph;
}

void PekingExpress::GameUpdate::UpdateBudgetCompetitor(const int id)
{

}

void PekingExpress::GameUpdate::UpdateBudgetOur()
{

}

void PekingExpress::GameUpdate::UpdateCompetitorLocation(const int groupid, const int location)
{
	ICouple* group = GetCompetitorById(groupid);

	if (group == nullptr)
	{
		return;
	}

	for (Node* node : graph->GetLocations())
	{
		if (node->GetId() == location)
		{
			group->SetCurrentPosition(node);
		}
	}
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

int PekingExpress::GameUpdate::NextMove()
{
	std::vector<bool> visitedNodes;

	for (bool el : graph->GetLocations())
	{
		visitedNodes.push_back(false);
	}

	std::vector<int> d(graph->GetLocations().size());

	std::queue<Node*> nodeQueue;

	nodeQueue.push(graph->GetLocations().front());
	visitedNodes.at(nodeQueue.front()->GetId() - OFFSET);

	while (!nodeQueue.empty())
	{
		int v = nodeQueue.front()->GetId() - OFFSET;
		nodeQueue.pop();

		for (auto nodeNumber : graph->GetLocations().at(v)->GetConnections())
		{
			if (visitedNodes.at(nodeNumber.GetNode()->GetId() - OFFSET) == false)
			{
				visitedNodes.at(nodeNumber.GetNode()->GetId() - OFFSET) = true;
				nodeQueue.push(graph->GetLocations().at(nodeNumber.GetNode()->GetId() - OFFSET));
				d.at(nodeNumber.GetNode()->GetId() - OFFSET) = d.at(v) + 1;
			}
		}
	}

	return d.at(graph->GetLocations().back()->GetId() - OFFSET);
}

void PekingExpress::GameUpdate::ApplyOurMove(const int location)
{
	UpdateOurLocation(location);
}

PekingExpress::GameUpdate::~GameUpdate()
{
	delete graph;
	delete ourCouple;

	for (ICouple* couple : competitors)
	{
		delete couple;
	}

	competitors.clear();
}
