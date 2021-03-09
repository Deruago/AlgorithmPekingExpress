#include "PekingExpress/Game/Model/Couple.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestCouple : public testing::Test
{
public:
	TestCouple() = default;
	~TestCouple() = default;
protected:
};

TEST_F(TestCouple, CreateEmptyCouple_CoupleCorrectlyCreated)
{
	const Couple couple = Couple(0, 0, nullptr);

	EXPECT_EQ(0, couple.GetBudget());
	EXPECT_EQ(0, couple.GetId());
	EXPECT_EQ(nullptr, couple.GetCurrentPosition());
}

TEST_F(TestCouple, CreateCouple_CoupleCorrectlyCreated)
{
	Node* expectedNode = new Node(1, {}, true);
	const Couple couple = Couple(1234, 54321, expectedNode);

	EXPECT_EQ(1234, couple.GetBudget());
	EXPECT_EQ(54321, couple.GetId());
	EXPECT_EQ(expectedNode, couple.GetCurrentPosition());

	delete expectedNode;
}

TEST_F(TestCouple, UpdateDataOfCouple_DataIsCorrectlyUpdated)
{
	Node* expectedNode = new Node(1, {}, true);
	Node* expectedNode2 = new Node(12, {}, false);
	
	Couple couple = Couple(1234, 543210, expectedNode);

	couple.SetBudget(-1000);
	couple.SetCurrentPosition(expectedNode2);
	
	EXPECT_EQ(-1000, couple.GetBudget());
	EXPECT_EQ(543210, couple.GetId());
	EXPECT_EQ(expectedNode2, couple.GetCurrentPosition());
	
	delete expectedNode;
	delete expectedNode2;
}