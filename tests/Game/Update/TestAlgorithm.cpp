#include "PekingExpress/Game/Update/Algorithm.h"
#include "PekingExpress/Game/Init/GraphBuilder.h"
#include <climits>
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestAlgorithm : public testing::Test
{
public:
	TestAlgorithm() = default;
	~TestAlgorithm() = default;
protected:
	void PopulateGraph(GraphBuilder& graphBuilder);
};

void TestAlgorithm::PopulateGraph(GraphBuilder& graphBuilder)
{
	graphBuilder.AddNode(1);
	graphBuilder.AddNode(2);
	graphBuilder.AddNode(3);
	graphBuilder.AddNode(88);
	graphBuilder.AddConnection(1, 2, 1);
	graphBuilder.AddConnection(1, 3, 3);
	graphBuilder.AddConnection(1, 88, 7);
	graphBuilder.AddConnection(2, 3, 1);
	graphBuilder.AddConnection(3, 88, 1);
}

TEST_F(TestAlgorithm, TestConstructor_FieldsSetCorrectly)
{
	GraphBuilder graphBuilder;
	PopulateGraph(graphBuilder);

	Graph* graph = graphBuilder.GetGraph();

	Algorithm alg = Algorithm(graph, nullptr);

	for (auto val : alg.dist)
	{
		if (val == alg.dist[0])
		{
			EXPECT_EQ(0, val);
		}
		else
		{
			EXPECT_EQ(INT_MAX, val);
		}
	}

	for (auto val : alg.sptSet)
	{
		EXPECT_EQ(false, val);
	}

	for (size_t i = 0; i < alg.graph->GetLocations().size(); i++)
	{
		EXPECT_EQ(i, alg.nodes[i].first);
		EXPECT_EQ(alg.graph->GetLocations()[i], alg.nodes[i].second);
	}

	for (auto val : alg.prev)
	{
		EXPECT_EQ(-1, val.first);
		EXPECT_EQ(nullptr, val.second);
	}

	delete graph;
}

TEST_F(TestAlgorithm, GetNodeWithMinimalDistance_GetNodeSuccesfully)
{
	GraphBuilder graphBuilder;
	PopulateGraph(graphBuilder);

	Graph* graph = graphBuilder.GetGraph();

	Algorithm alg = Algorithm(graph, nullptr);
	std::pair<int, PekingExpress::Node*> res1 = alg.MinDistance(alg.dist, alg.sptSet, alg.nodes);

	EXPECT_EQ(0, res1.first);

	alg.dist[1] = 1;
	alg.dist[2] = 2;
	alg.dist[3] = 3;

	alg.sptSet[0] = true;

	std::pair<int, PekingExpress::Node*> res2 = alg.MinDistance(alg.dist, alg.sptSet, alg.nodes);

	EXPECT_EQ(1, res2.first);

	alg.sptSet[1] = true;

	std::pair<int, PekingExpress::Node*> res3 = alg.MinDistance(alg.dist, alg.sptSet, alg.nodes);

	EXPECT_EQ(2, res3.first);

	alg.sptSet[2] = true;

	std::pair<int, PekingExpress::Node*> res4 = alg.MinDistance(alg.dist, alg.sptSet, alg.nodes);

	EXPECT_EQ(3, res4.first);

	delete graph;
}

TEST_F(TestAlgorithm, GetAllNeighboursOfAVertex_GetVerticesSuccesfully)
{
	GraphBuilder graphBuilder;
	PopulateGraph(graphBuilder);

	Graph* graph = graphBuilder.GetGraph();

	Algorithm alg = Algorithm(graph, nullptr);

	std::pair<int, Node*> u = alg.MinDistance(alg.dist, alg.sptSet, alg.nodes);

	std::vector<std::pair<int, Node*>> resNodes;

	for (auto neighbour : u.second->GetConnections())
	{
		std::pair<int, Node*> v = alg.GetVertex(alg.nodes, neighbour);
		resNodes.push_back(v);
	}

	EXPECT_EQ(1, resNodes[0].first);
	EXPECT_EQ(2, resNodes[1].first);
	EXPECT_EQ(3, resNodes[2].first);

	delete graph;
}

TEST_F(TestAlgorithm, GetCorrectDistanceAndPathOfSourceToTarget_GetDistanceAndPathSuccesfully)
{
	GraphBuilder graphBuilder;
	PopulateGraph(graphBuilder);

	Graph* graph = graphBuilder.GetGraph();

	Algorithm alg = Algorithm(graph, nullptr);

	alg.DoAlgorithm();

	EXPECT_EQ(0, alg.dist[0]);
	EXPECT_EQ(1, alg.dist[1]);
	EXPECT_EQ(2, alg.dist[2]);
	EXPECT_EQ(3, alg.dist[3]);

	EXPECT_EQ(0, alg.path[0].first);
	EXPECT_EQ(1, alg.path[1].first);
	EXPECT_EQ(2, alg.path[2].first);
	EXPECT_EQ(3, alg.path[3].first);

	delete graph;
}

TEST_F(TestAlgorithm, GetCorrectPathGivenTwoOptions_GetCorrectPath)
{
	GraphBuilder graphBuilder;

	graphBuilder.AddNode(1);
	graphBuilder.AddNode(2);
	graphBuilder.AddNode(3);
	graphBuilder.AddNode(4);

	graphBuilder.AddConnection(1, 2, 2);
	graphBuilder.AddConnection(1, 3, 3);
	graphBuilder.AddConnection(3, 4, 1);
	graphBuilder.AddConnection(2, 4, 4);

	Graph* graph = graphBuilder.GetGraph();

	Algorithm alg = Algorithm(graph, nullptr);

	alg.DoAlgorithm();

	EXPECT_EQ(0, alg.dist[0]);
	EXPECT_EQ(2, alg.dist[1]);
	EXPECT_EQ(3, alg.dist[2]);
	EXPECT_EQ(4, alg.dist[3]);

	EXPECT_EQ(0, alg.path[0].first);
	EXPECT_EQ(2, alg.path[1].first);
	EXPECT_EQ(3, alg.path[2].first);

	delete graph;
}

TEST_F(TestAlgorithm, GetCorrectPathWithCouple_GetCorrectPath)
{
	GraphBuilder graphBuilder;
	PopulateGraph(graphBuilder);

	Graph* graph = graphBuilder.GetGraph();
	Couple* couple = new Couple(100, 1, graph->GetLocations()[0]);

	Algorithm alg = Algorithm(graph, nullptr);

	alg.DoAlgorithm();

	EXPECT_EQ(0, alg.path[0].first);
	EXPECT_EQ(1, alg.path[1].first);
	EXPECT_EQ(2, alg.path[2].first);
	EXPECT_EQ(3, alg.path[3].first);

	delete graph;
	delete couple;
}