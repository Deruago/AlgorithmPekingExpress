#include "PekingExpress/Game/Model/Node.h"

#include <iostream>

PekingExpress::Node::Node(const int id_, const std::vector<Connection>& connections_, bool isCritical)
	:	Id_(id_),
		Critical(isCritical),
		Connections(connections_)
{
}

void PekingExpress::Node::AddConnection(Connection connection)
{
	//std::cout << "Connection added!" << " From: " << GetId() << " To: " << connection.GetNode()->GetId() << '\n';
	Connections.push_back(connection);
}

const std::vector<PekingExpress::Connection>& PekingExpress::Node::GetConnections() const
{
	return Connections;
}

int PekingExpress::Node::GetId() const
{
	return Id_;
}

bool PekingExpress::Node::IsCritical() const
{
	return Critical;
}
