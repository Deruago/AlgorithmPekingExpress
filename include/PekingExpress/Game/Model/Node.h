#ifndef PEKINGEXPRESS_GAME_MODEL_NODE_H
#define PEKINGEXPRESS_GAME_MODEL_NODE_H

#include "PekingExpress/Game/Model/Connection.h"
#include <vector>

namespace PekingExpress
{
	class Node
	{
	public:
		Node(int id_, const std::vector<Connection>& connections_, bool isCritical);
		~Node() = default;

		void AddConnection(Connection connection);

		const std::vector<Connection>& GetConnections() const;
		int GetId() const;
		bool IsCritical() const;
	private:
		const int Id_;
		const bool Critical;
		std::vector<Connection> Connections;
	};
}

#endif //PEKINGEXPRESS_GAME_MODEL_NODE_H