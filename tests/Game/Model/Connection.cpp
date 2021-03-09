#include "PekingExpress/Game/Model/Connection.h"
#include "PekingExpress/Game/Model/Node.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestConnection : public testing::Test
{
public:
	TestConnection() = default;
	~TestConnection() = default;
protected:
};

TEST_F(TestConnection, CreateEmptyConnection_ConnectionIsCorrectlyGenerated)
{
	const Connection actual = Connection(nullptr, 0);

	EXPECT_EQ(nullptr, actual.GetNode());
	EXPECT_EQ(0, actual.GetPrice());
}

TEST_F(TestConnection, CreateConnection_ConnectionIsCorrectlyGenerated)
{
	Node* expectedNode = new Node(100, {}, true);
	
	const Connection actual = Connection(expectedNode, 1234);

	EXPECT_EQ(expectedNode, actual.GetNode());
	EXPECT_EQ(1234, actual.GetPrice());

	delete expectedNode;
}