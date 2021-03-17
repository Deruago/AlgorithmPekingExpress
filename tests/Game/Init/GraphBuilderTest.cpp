#include "PekingExpress/Game/Init/GraphBuilder.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestGraphBuilder : public testing::Test
{
public:
	TestGraphBuilder() = default;
	~TestGraphBuilder() = default;
protected:
	Graph emptyGraph = Graph({});
};

TEST_F(TestGraphBuilder, CreateEmptyGraph_GraphIsCorrectlyGenerated)
{
	GraphBuilder graphBuilder;
	Graph* res = graphBuilder.GetGraph();

	EXPECT_EQ(emptyGraph.GetLocations(), res->GetLocations());
}

TEST_F(TestGraphBuilder, CreateGraphWithOneNode_GraphIsCorrectlyGenerated)
{
	GraphBuilder graphBuilder;

	graphBuilder.AddNode(1);
	Graph* res = graphBuilder.GetGraph();

	EXPECT_EQ(1, res->GetLocations()[0]->GetId());
}

TEST_F(TestGraphBuilder, CreateGraphWithMultipleNodes_GraphIsCorrectlyGenerated)
{
	GraphBuilder graphBuilder;

	graphBuilder.AddNode(1);
	graphBuilder.AddNode(2);
	graphBuilder.AddNode(3);
	Graph* res = graphBuilder.GetGraph();

	EXPECT_EQ(1, res->GetLocations()[0]->GetId());
	EXPECT_EQ(2, res->GetLocations()[1]->GetId());
	EXPECT_EQ(3, res->GetLocations()[2]->GetId());
}

TEST_F(TestGraphBuilder, CreateGraphWithTwoNodesAndAConnection_GraphIsCorrectlyGenerated)
{
	GraphBuilder graphBuilder;

	graphBuilder.AddNode(1);
	graphBuilder.AddNode(2);
	graphBuilder.AddConnection(1, 2, 0);
	Graph* res = graphBuilder.GetGraph();

	EXPECT_EQ(1, res->GetLocations()[0]->GetId());
	EXPECT_EQ(2, res->GetLocations()[1]->GetId());
	EXPECT_EQ(2, res->GetLocations()[0]->GetConnections()[0].GetNode()->GetId());
}

TEST_F(TestGraphBuilder, CreateGraphWithTwoNodesAndAConnectionWithPrice_GraphIsCorrectlyGenerated)
{
	GraphBuilder graphBuilder;

	graphBuilder.AddNode(1);
	graphBuilder.AddNode(2);
	graphBuilder.AddConnection(1, 2, 5);
	Graph* res = graphBuilder.GetGraph();

	EXPECT_EQ(1, res->GetLocations()[0]->GetId());
	EXPECT_EQ(2, res->GetLocations()[1]->GetId());
	EXPECT_EQ(2, res->GetLocations()[0]->GetConnections()[0].GetNode()->GetId());
	EXPECT_EQ(5, res->GetLocations()[0]->GetConnections()[0].GetPrice());
}

TEST_F(TestGraphBuilder, CreateGraphWithOneCriticalNode_GraphIsCorrectlyGenerated)
{
	GraphBuilder graphBuilder;

	graphBuilder.AddCriticalNode(1);
	Graph* res = graphBuilder.GetGraph();

	EXPECT_EQ(1, res->GetLocations()[0]->GetId());
	EXPECT_EQ(true, res->GetLocations()[0]->IsCritical());
}

TEST_F(TestGraphBuilder, CreateGraphWithAConnectionBetweenACriticalNodeAndNormalNode_GraphIsCorrectlyGenerated)
{
	GraphBuilder graphBuilder;

	graphBuilder.AddCriticalNode(1);
	graphBuilder.AddNode(2);
	graphBuilder.AddConnection(1, 2, 0);
	Graph* res = graphBuilder.GetGraph();

	EXPECT_EQ(1, res->GetLocations()[0]->GetId());
	EXPECT_EQ(2, res->GetLocations()[1]->GetId());
	EXPECT_EQ(true, res->GetLocations()[0]->IsCritical());
	EXPECT_EQ(2, res->GetLocations()[0]->GetConnections()[0].GetNode()->GetId());
}