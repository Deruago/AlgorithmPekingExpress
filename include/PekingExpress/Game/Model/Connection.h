#ifndef PEKINGEXPRESS_GAME_MODEL_CONNECTION_H
#define PEKINGEXPRESS_GAME_MODEL_CONNECTION_H

namespace PekingExpress
{
	class Node;

	class Connection
	{
	private:
		const Node* Node_;
		const int Price_;
	public:
		Connection(Node* const node_, const int price_ = 0);
		~Connection() = default;
	public:
		const Node* GetNode() const;
		int GetPrice() const;

		bool operator==(const Connection connection) const
		{
			return
			(connection.GetNode() == this->GetNode())
			&& (connection.GetPrice() == this->GetPrice());
		}

	};
}

#endif //PEKINGEXPRESS_GAME_MODEL_CONNECTION_H