#include "PekingExpress/Game/Update/GameUpdate.h"
#include "PekingExpress/Game/Model/Graph.h"
#include "PekingExpress/Game/Model/Couple.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestGameUpdate : public testing::Test
{
public:
	TestGameUpdate() = default;
	~TestGameUpdate() = default;
protected:
};

TEST_F(TestGameUpdate, CreateNormalGameUpdate_GameUpdateIsCorrectlyCreated)
{
	Graph graph = Graph({});
	Couple couple = Couple(0, 0, nullptr);
	Couple competitor1 = Couple(0, 1, nullptr);
	Couple competitor2 = Couple(0, 2, nullptr);
	const std::vector<Couple*> competitors = { &competitor1, &competitor2 };
	const GameUpdate gameUpdate = GameUpdate(&graph, &couple, competitors);

	EXPECT_EQ(competitor1, gameUpdate.GetCompetitorById(1));
	EXPECT_EQ(competitor2, gameUpdate.GetCompetitorById(2));
	EXPECT_EQ(couple, gameUpdate.GetAllCouples().at(0));
	EXPECT_EQ(graph, *(gameUpdate.GetGraph()));
}

// General class tests

TEST_F(TestGameUpdate, UpdateCoupleLocation_CoupleLocationIsSuccesfullyUpdated)
{

}

TEST_F(TestGameUpdate, UpdateCoupleLocation_CoupleLocationIsSuccesfullyUpdated)
{

}

TEST_F(TestGameUpdate, UpdateCoupleWithNullpointerCouple_CoupleLocationIsNotUpdated)
{

}

TEST_F(TestGameUpdate, UpdateCoupleWithLocationNotOnGraph_CoupleLocationIsNotUpdated)
{

}

// Calculate next move without price

TEST_F(TestGameUpdate, GetNextMoveBetweenTwoNodes_NextMoveSuccesfullyReturned)
{
	// X -- X
}

TEST_F(TestGameUpdate, GetNextMoveBetweenTwoCriticalNodes_NextMoveSuccesfullyReturned)
{
	// CN -- CN
}

TEST_F(TestGameUpdate, GetNextMoveWithThreeNodesAndACompetitorBlockingTheWay_NextMoveSuccesfullyReturned)
{
	// X -- X (C) -- X
}

TEST_F(TestGameUpdate, GetNextMoveWithTwoNodesAndACriticalNodeWhileACompetitorIsBlockingTheWay_NextMoveNotFound)
{
	// X -- CN (C) -- X
}

TEST_F(TestGameUpdate, GetNextMoveWithOneNode_NextMoveSuccesfullyReturned)
{
	// X
}

// With price

TEST_F(TestGameUpdate, GetNextMoveWithTwoNodesAndConnectionPriceLowerThanBudget_NextMoveSuccesfullyFound)
{
	// X -- X
}

TEST_F(TestGameUpdate, GetNextMoveWithTwoNodesAndConnectionPriceHigherThanBudget_NextMoveNotFound)
{
	// X -- X
}

TEST_F(TestGameUpdate, GetNextMoveWithThreeNodesAndConnectionToGoalPriceHigherThanMultipleNodeRoute_NextMoveSuccesfullyFound)
{
	// X -- X -- X
	// |_________| <- price higher
}

TEST_F(TestGameUpdate, GetNextMoveWithTwoNodesAndConnectionToGoalPriceLowerThanMultipleNodeRoute_NextMoveSuccesfullyFound)
{
	// X -- X -- X
	// |_________| <- price lower
}

TEST_F(TestGameUpdate, GetNextMoveWithThreeNodesWithCompetitorOnACriticalNodeAndConnectionToGoalNodeHasLowerPrice_NextMoveSuccesfullyFound)
{
	//  X -- CN (C) -- X
	//  |______________| <- lower price connection		
}

TEST_F(TestGameUpdate, GetNextMoveWithThreeNodesWithCompetitorOnACriticalNodeAndConnectionToGoalNodeHasHigherPricePrice_NextMoveSuccesfullyFound)
{
	//  X -- CN (C) -- X
	//  |______________| <- higher price connection		
}