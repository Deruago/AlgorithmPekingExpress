#include "PekingExpress/Game/Model/Node.h"
#include "PekingExpress/Game/Model/Graph.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

/*!	\class TestCreateGraph
 *
 *	\brief This integration test, tests if we can correctly create, and use graphs and related types.
 */
class TestCreateGraph : public testing::Test
{
public:
	TestCreateGraph() = default;
	~TestCreateGraph() = default;
protected:
	const std::vector<Node*> emptyNodes = {};
	const std::vector<Node*> nullpointerNodes = { nullptr };
};

std::vector<Node*> GenerateConnectedNodes(const std::size_t total)
{
	std::vector<Node*> nodes;
	for(auto i = 0; i < total; i++)
	{
		bool isCritical = false;
		if ((i % 2) == 1)
		{
			isCritical = true;
		}
		nodes.push_back(new Node(i, {}, isCritical));
	}

	for(auto i = 0; i < total; i++)
	{
		for(auto j = 0; j < total; j++)
		{
			const auto nodePrice = (i * j) - j + i;
			nodes[i]->AddConnection(Connection(nodes[j], nodePrice));
		}
	}

	return nodes;
}

TEST_F(TestCreateGraph, TestCreationOfGrid)
{
	const auto expectedTotal = 10;
	const Graph graph = Graph(GenerateConnectedNodes(expectedTotal));

	EXPECT_EQ(expectedTotal, graph.GetLocations().size());
	EXPECT_EQ(expectedTotal / 2, graph.GetCriticalLocations().size());

	EXPECT_EQ(expectedTotal, graph.GetLocations()[0]->GetConnections().size());
}