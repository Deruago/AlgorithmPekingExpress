#include "PekingExpress/Game/Update/GameUpdate.h"
#include "PekingExpress/Game/Model/Graph.h"
#include "PekingExpress/Game/Model/Couple.h"
#include "PekingExpress/Game/Model/Connection.h"
#include "PekingExpress/Game/Init/GraphBuilder.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestGameUpdate : public testing::Test
{
public:
	TestGameUpdate() = default;
	~TestGameUpdate() = default;
protected:
	void PopulateGraph(GraphBuilder& graphBuilder);
};

void TestGameUpdate::PopulateGraph(GraphBuilder& graphBuilder)
{
	graphBuilder.AddNode(1);
	graphBuilder.AddNode(2);
	graphBuilder.AddCriticalNode(3);
	graphBuilder.AddNode(88);
	graphBuilder.AddConnection(1, 2, 1);
	graphBuilder.AddConnection(1, 3, 3);
	graphBuilder.AddConnection(1, 88, 7);
	graphBuilder.AddConnection(2, 3, 1);
	graphBuilder.AddConnection(3, 88, 1);
}

// General class tests

TEST_F(TestGameUpdate, CreateNormalGameUpdate_GameUpdateIsCorrectlyCreated)
{
	Graph graph = Graph({});
	Couple couple = Couple(0, 0, nullptr);
	Couple competitor1 = Couple(0, 1, nullptr);
	Couple competitor2 = Couple(0, 2, nullptr);
	const std::vector<Couple*> competitors = { &competitor1, &competitor2 };
	const GameUpdate gameUpdate = GameUpdate(&graph, &couple, competitors);

	EXPECT_EQ(competitor1.GetId(), gameUpdate.GetCompetitorById(1)->GetId());
	EXPECT_EQ(competitor2.GetId(), gameUpdate.GetCompetitorById(2)->GetId());
	EXPECT_EQ(couple.GetId(), gameUpdate.GetAllCouples().at(0)->GetId());
}

TEST_F(TestGameUpdate, GeneralTestOne_MovesAreCorrectlyGenerated)
{
	GraphBuilder graphBuilder;
	PopulateGraph(graphBuilder);

	Graph* graph = graphBuilder.GetGraph();
	Couple* couple = new Couple(5, 1, graph->GetLocations()[0]);

	GameUpdate gameUpdate = GameUpdate(graph, couple, { 0 });

	Node* node1 = graph->GetLocations()[0];
	Node* node2 = graph->GetLocations()[1];
	Node* node3 = graph->GetLocations()[2];
	Node* node4 = graph->GetLocations()[3];

	// Begin turn 1
	const Move* nextMove1 = gameUpdate.NextMove();

	EXPECT_EQ(gameUpdate.GetPath()[0].second, nextMove1->GetStartLocation());
	EXPECT_EQ(gameUpdate.GetPath()[1].second, nextMove1->GetEndLocation());

	couple->SetCurrentPosition(graph->GetLocations()[1]);
	gameUpdate.UpdateOccupiedLocations({ node2, node3 });
	// End turn 1

	// Begin turn 2
	Move* nextMove2 = gameUpdate.NextMove();

	EXPECT_EQ(gameUpdate.GetPath()[1].second, nextMove2->GetStartLocation());
	EXPECT_EQ(gameUpdate.GetPath()[1].second, nextMove2->GetEndLocation());

	couple->SetCurrentPosition(graph->GetLocations()[1]);
	gameUpdate.UpdateOccupiedLocations({ node3 });
	// End turn 2

	// Begin turn 3
	Move* nextMove3 = gameUpdate.NextMove();

	EXPECT_EQ(gameUpdate.GetPath()[1].second, nextMove3->GetStartLocation());
	EXPECT_EQ(gameUpdate.GetPath()[1].second, nextMove3->GetEndLocation());

	couple->SetCurrentPosition(graph->GetLocations()[1]);
	gameUpdate.UpdateOccupiedLocations({ node4 });
	// End turn 3

	// Begin turn 4
	Move* nextMove4 = gameUpdate.NextMove();

	EXPECT_EQ(gameUpdate.GetPath()[1].second, nextMove4->GetStartLocation());
	EXPECT_EQ(gameUpdate.GetPath()[2].second, nextMove4->GetEndLocation());

	couple->SetCurrentPosition(graph->GetLocations()[2]);
	gameUpdate.UpdateOccupiedLocations({ node4 });
	// End turn 4

	// Begin turn 5
	Move* nextMove5 = gameUpdate.NextMove();

	EXPECT_EQ(gameUpdate.GetPath()[2].second, nextMove5->GetStartLocation());
	EXPECT_EQ(gameUpdate.GetPath()[3].second, nextMove5->GetEndLocation());

	couple->SetCurrentPosition(graph->GetLocations()[3]);
	gameUpdate.UpdateOccupiedLocations({ node4 });
	// End turn 5

	EXPECT_EQ(gameUpdate.GetGraph()->GetLocations()[3], couple->GetCurrentPosition());

	delete graph;
	delete couple;
	delete nextMove1;
	delete nextMove2;
	delete nextMove3;
	delete nextMove4;
	delete nextMove5;
}
