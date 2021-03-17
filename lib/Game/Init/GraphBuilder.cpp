#include "PekingExpress/Game/Init/GraphBuilder.h"

bool PekingExpress::GraphBuilder::IsDuplicate(int id)
{
	for (auto node : graphNodes)
	{
		if (node->GetId() == id)
		{
			return true;
		}
	}

	return false;
}

void PekingExpress::GraphBuilder::AddNode(int nodeId, bool isCritical)
{
	if (IsDuplicate(nodeId))
	{
		return;
	}

	Node* node = new Node(nodeId, {}, isCritical);
	graphNodes.push_back(node);
}

void PekingExpress::GraphBuilder::AddCriticalNode(int nodeId)
{
	AddNode(nodeId, true);
}

void PekingExpress::GraphBuilder::AddConnection(int sourceNode, int destinationNode, int price)
{
	Node* tempSourceNode = nullptr;
	Node* tempDestNode = nullptr;

	for (auto node : graphNodes)
	{
		if (node->GetId() == sourceNode)
		{
			tempSourceNode = node;
		}

		if (node->GetId() == destinationNode)
		{
			tempDestNode = node;
		}
	}

	if (tempSourceNode == nullptr || tempDestNode == nullptr)
	{
		return;
	}

	tempSourceNode->AddConnection(Connection(tempDestNode, price));
}

PekingExpress::Graph* PekingExpress::GraphBuilder::GetGraph() const
{
	return new Graph(graphNodes);
}
