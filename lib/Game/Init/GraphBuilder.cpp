#include "PekingExpress/Game/Init/GraphBuilder.h"

PekingExpress::GraphBuilder::GraphBuilder()
{

}

void PekingExpress::GraphBuilder::AddNode(int nodeId)
{
	Node* node = new Node(nodeId, {}, false);
	graphNodes.push_back(node);
}

void PekingExpress::GraphBuilder::AddCriticalNode(int nodeId)
{
	Node* node = new Node(nodeId, {}, true);
	graphNodes.push_back(node);
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

PekingExpress::GraphBuilder::~GraphBuilder()
{
	for (auto node : graphNodes)
	{
		delete node;
	}
}

