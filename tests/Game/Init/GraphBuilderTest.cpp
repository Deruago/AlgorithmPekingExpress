#include "PekingExpress/Game/Init/GraphBuilder.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestGraphBuilder : public testing::Test
{
public:
	TestGraphBuilder() = default;
	~TestGraphBuilder() = default;
protected:
	GraphBuilder graphBuilder;
	Graph emptyGraph = Graph({});
};

TEST_F(TestGraphBuilder, CreateEmptyGraph_GraphIsCorrectlyGenerated)
{
	IGraph* res = graphBuilder.GetGraph();

	EXPECT_EQ(emptyGraph, res);
}