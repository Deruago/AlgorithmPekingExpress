#include "PekingExpress/Game/Init/JsonToGraph.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestJsonToGraph : public testing::Test
{
public:
	TestJsonToGraph() = default;
	~TestJsonToGraph() = default;
protected:
};

TEST_F(TestJsonToGraph, TestJsonParsing)
{
	JsonToGraph json;
	auto* graph = json.ConvertJsonToGraph("{ \"locations\": {\"number\":4, \"critical\" : [3] },\"connections\" : {\"source\": [1, 1, 1, 2, 3] , \"target\" : [2, 3, 88, 3, 88] ,\"price\" : [1, 3, 7, 1, 1] } }");
	
	EXPECT_EQ(4, graph->GetLocations().size());
	EXPECT_EQ(1, graph->GetCriticalLocations().size());

	EXPECT_EQ(3, graph->GetLocations()[0]->GetId());
	EXPECT_EQ(1, graph->GetLocations()[1]->GetId());
	EXPECT_EQ(2, graph->GetLocations()[2]->GetId());
	EXPECT_EQ(88, graph->GetLocations()[3]->GetId());

	delete graph;
}