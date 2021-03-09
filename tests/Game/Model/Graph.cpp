#include "PekingExpress/Game/Model/Node.h"
#include "PekingExpress/Game/Model/Graph.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestGraph : public testing::Test
{
public:
	TestGraph() = default;
	~TestGraph() = default;
protected:
	const std::vector<Node*> emptyNodes = {};
	const std::vector<Node*> nullpointerNodes = {nullptr};
};

TEST_F(TestGraph, CreateEmptyGraphWithNullpointerNode_GraphIsCorrectlyCreated)
{
	const Graph graph = Graph({nullptr});
	
	EXPECT_EQ(nullpointerNodes, graph.GetLocations());
	EXPECT_EQ(emptyNodes, graph.GetCriticalLocations());
}

TEST_F(TestGraph, CreateEmptyGraph_GraphIsCorrectlyCreated)
{
	const Graph graph = Graph({});

	EXPECT_EQ(emptyNodes, graph.GetLocations());
	EXPECT_EQ(emptyNodes, graph.GetCriticalLocations());
}

TEST_F(TestGraph, CreateGraphWithCriticalNode_GraphIsCorrectlyCreated)
{
	Node* expectedNode = new Node(1234, {}, true);
	const std::vector<Node*> expectedNodes = { expectedNode };
	
	const Graph graph = Graph({expectedNode});

	EXPECT_EQ(expectedNodes, graph.GetLocations());
	EXPECT_EQ(expectedNodes, graph.GetCriticalLocations());
}

TEST_F(TestGraph, CreateGraphWithNormalNode_GraphIsCorrectlyCreated)
{
	Node* expectedNode = new Node(1234, {}, false);
	const std::vector<Node*> expectedNodes = { expectedNode };

	const Graph graph = Graph({ expectedNode });

	EXPECT_EQ(expectedNodes, graph.GetLocations());
	EXPECT_EQ(emptyNodes, graph.GetCriticalLocations());
}

TEST_F(TestGraph, CreateGraphWithMultipleNormalNodes_GraphIsCorrectlyCreated)
{
	Node* expectedNode1 = new Node(1234, {}, false);
	Node* expectedNode2 = new Node(1234, {}, false);
	const std::vector<Node*> nodes = { expectedNode1, expectedNode2 };

	const Graph graph = Graph({ expectedNode1, expectedNode2 });

	EXPECT_EQ(nodes, graph.GetLocations());
	EXPECT_EQ(emptyNodes, graph.GetCriticalLocations());
}

TEST_F(TestGraph, CreateGraphWithMultipleCriticalNodes_GraphIsCorrectlyCreated)
{
	Node* expectedNode1 = new Node(1234, {}, true);
	Node* expectedNode2 = new Node(1234, {}, true);
	const std::vector<Node*> nodes = { expectedNode1, expectedNode2 }; 

	const Graph graph = std::vector<Node*>({ expectedNode1, expectedNode2 });

	EXPECT_EQ(nodes, graph.GetLocations());
	EXPECT_EQ(nodes, graph.GetCriticalLocations());
}

TEST_F(TestGraph, CreateGraphWithMultipleCriticalNodesAndNormalNodes_GraphIsCorrectlyCreated)
{
	Node* expectedCriticalNode1 = new Node(1234, {}, true);
	Node* expectedCriticalNode2 = new Node(1234, {}, true);
	
	Node* expectedNode1 = new Node(1234, {}, false);
	Node* expectedNode2 = new Node(1234, {}, false);
	
	const std::vector<Node*> nodes = { expectedCriticalNode1, expectedNode1, expectedCriticalNode2, expectedNode2 };
	const std::vector<Node*> criticalNodes = { expectedCriticalNode1, expectedCriticalNode2 };

	const Graph graph = Graph({ expectedCriticalNode1, expectedNode1, expectedCriticalNode2, expectedNode2 });


	EXPECT_EQ(nodes, graph.GetLocations());
	EXPECT_EQ(criticalNodes, graph.GetCriticalLocations());
}