#include "PekingExpress/Game/Model/Connection.h"
#include "PekingExpress/Game/Model/Node.h"
#include <gtest/gtest.h>

using namespace PekingExpress;

class TestNode : public testing::Test
{
public:
	TestNode() = default;
	~TestNode() = default;
protected:
};

TEST_F(TestNode, CreateEmptyNode_NodeCorrectlyCreated)
{
	const Node node = Node(0, {}, false);
	const std::vector<Connection> connections = { };

	EXPECT_EQ(0, node.GetId());

	auto actualConnections = node.GetConnections();
	EXPECT_EQ(connections, actualConnections);
	EXPECT_EQ(false, node.IsCritical());
}

TEST_F(TestNode, CreateNode_NodeCorrectlyCreated)
{
	const std::vector<Connection> connections = { Connection(nullptr, 1111) };
	const Node node = Node(1234, connections, true);

	EXPECT_EQ(1234, node.GetId());

	const auto actualConnections = node.GetConnections();
	EXPECT_EQ(connections, actualConnections);
	EXPECT_EQ(true, node.IsCritical());
}

TEST_F(TestNode, AddConnection_NodeCorrectlyUpdatesConnections)
{
	const auto connection = Connection(nullptr, 1111);
	const std::vector<Connection> connections = { connection };
	Node node = Node(1234, {}, true);

	node.AddConnection(connection);

	EXPECT_EQ(1, node.GetConnections().size());

	const auto actualConnections = node.GetConnections();
	EXPECT_EQ(connections, actualConnections);

	EXPECT_EQ(1234, node.GetId());
	EXPECT_EQ(true, node.IsCritical());
}

TEST_F(TestNode, AddConnections_NodeCorrectlyUpdatesConnections)
{
	const auto connection1 = Connection(nullptr, 1111);
	const auto connection2 = Connection(nullptr, 1111);
	const std::vector<Connection> connections = { connection1, connection2 };
	Node node = Node(1234, {}, true);

	node.AddConnection(connection1);
	node.AddConnection(connection2);

	EXPECT_EQ(2, node.GetConnections().size());

	const auto actualConnections = node.GetConnections();
	EXPECT_EQ(connections, actualConnections);

	EXPECT_EQ(1234, node.GetId());
	EXPECT_EQ(true, node.IsCritical());
}