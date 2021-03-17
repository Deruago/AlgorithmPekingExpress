#include "PekingExpress/Game/Update/GameUpdate.h"
#include "PekingExpress/Game/Model/Graph.h"
#include "PekingExpress/Game/Model/Couple.h"
#include "PekingExpress/Game/Model/Connection.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestGameUpdate : public testing::Test
{
public:
	TestGameUpdate() = default;
	~TestGameUpdate() = default;
protected:
};

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

//TEST_F(TestGameUpdate, UpdateCoupleLocation_CoupleLocationIsSuccesfullyUpdated)
//{
//	EXPECT_EQ(0, 0);
//}

//TEST_F(TestGameUpdate, UpdateCoupleLocation_CoupleLocationIsSuccesfullyUpdated)
//{
//	EXPECT_EQ(0, 0);
//}
//
//TEST_F(TestGameUpdate, UpdateCoupleWithNullpointerCouple_CoupleLocationIsNotUpdated)
//{
//	EXPECT_EQ(0, 0);
//}
//
//TEST_F(TestGameUpdate, UpdateCoupleWithLocationNotOnGraph_CoupleLocationIsNotUpdated)
//{
//
//}

// Calculate next move without price

TEST_F(TestGameUpdate, GetNextMoveBetweenTwoNodes_NextMoveSuccesfullyReturned)
{
	// X -- X -- X
	Node* node1 = new Node(1, {}, false);
	Node* node2 = new Node(2, {}, false);
	Node* node3 = new Node(3, {}, false);
	Connection con1 = Connection(node2, 0);
	Connection con2 = Connection(node3, 0);
	node1->AddConnection(con1);
	node2->AddConnection(con2);
	Graph graph = Graph({ node1, node2, node3 });
	Couple couple = Couple(0, 1, node1);
	GameUpdate gameUpdate = GameUpdate(&graph, &couple, {});

	const int res = gameUpdate.NextMove();

	EXPECT_EQ(res, 2);
}

//TEST_F(TestGameUpdate, GetNextMoveBetweenTwoCriticalNodes_NextMoveSuccesfullyReturned)
//{
//	// CN -- CN
//	EXPECT_EQ(0, 0);
//}
//
//TEST_F(TestGameUpdate, GetNextMoveWithThreeNodesAndACompetitorBlockingTheWay_NextMoveSuccesfullyReturned)
//{
//	// X -- X (C) -- X
//	EXPECT_EQ(0, 0);
//}
//
//TEST_F(TestGameUpdate, GetNextMoveWithTwoNodesAndACriticalNodeWhileACompetitorIsBlockingTheWay_NextMoveNotFound)
//{
//	// X -- CN (C) -- X
//	EXPECT_EQ(0, 0);
//}
//
//TEST_F(TestGameUpdate, GetNextMoveWithOneNode_NextMoveSuccesfullyReturned)
//{
//	// X
//	EXPECT_EQ(0, 0);
//}
//
//// With price
//
//TEST_F(TestGameUpdate, GetNextMoveWithTwoNodesAndConnectionPriceLowerThanBudget_NextMoveSuccesfullyFound)
//{
//	// X -- X
//	EXPECT_EQ(0, 0);
//}
//
//TEST_F(TestGameUpdate, GetNextMoveWithTwoNodesAndConnectionPriceHigherThanBudget_NextMoveNotFound)
//{
//	// X -- X
//	EXPECT_EQ(0, 0);
//}
//
//TEST_F(TestGameUpdate, GetNextMoveWithThreeNodesAndConnectionToGoalPriceHigherThanMultipleNodeRoute_NextMoveSuccesfullyFound)
//{
//	// X -- X -- X
//	// |_________| <- price higher
//	EXPECT_EQ(0, 0);
//}
//
//TEST_F(TestGameUpdate, GetNextMoveWithTwoNodesAndConnectionToGoalPriceLowerThanMultipleNodeRoute_NextMoveSuccesfullyFound)
//{
//	// X -- X -- X
//	// |_________| <- price lower
//	EXPECT_EQ(0, 0);
//}
//
//TEST_F(TestGameUpdate, GetNextMoveWithThreeNodesWithCompetitorOnACriticalNodeAndConnectionToGoalNodeHasLowerPrice_NextMoveSuccesfullyFound)
//{
//	//  X -- CN (C) -- X
//	//  |______________| <- lower price connection		
//	EXPECT_EQ(0, 0);
//}
//
//TEST_F(TestGameUpdate, GetNextMoveWithThreeNodesWithCompetitorOnACriticalNodeAndConnectionToGoalNodeHasHigherPricePrice_NextMoveSuccesfullyFound)
//{
//	//  X -- CN (C) -- X
//	//  |______________| <- higher price connection		
//	EXPECT_EQ(0, 0);
//}