#ifndef PEKINGEXPRESS_GAME_UPDATE_GAMEUPDATE_H
#define PEKINGEXPRESS_GAME_UPDATE_GAMEUPDATE_H

#include "PekingExpress/Game/Model/Graph.h"
#include "PekingExpress/Game/Model/Couple.h"
#include "PekingExpress/Game/Model/Node.h"
#include "PekingExpress/Game/Model/Move.h"

namespace PekingExpress
{
	class GameUpdate
	{
	private:
		Graph* graph;
		Couple* ourCouple;
		std::vector<Couple*> competitors;
		std::vector<Node*> occupiedNodes;
		std::vector<std::pair<int, Node*>> path;

		bool IsVacantCriticalNode(Node* node);

	public:
		GameUpdate(Graph* graph_, Couple* ourCouple_, std::vector<Couple*> competitors_);
		~GameUpdate() = default;

		Couple* GetCompetitorById(const int id) const;
		std::vector<Couple*> GetAllCouples() const;
		const Graph* GetGraph() const;
		void UpdateBudgetOur(int newBudget);
		void UpdateOccupiedLocations(std::vector<Node*> nodes);
		void UpdateOurLocation(const Move* location);
		Move* NextMove();
		void ApplyOurMove(const Move* location);
		Node* GetNextNodeInPath();
		Connection* GetConnection(Node* startNode, Node* endNode);

		const std::vector<std::pair<int, Node*>> GetPath() const;
	};
}

#endif //PEKINGEXPRESS_GAME_UPDATE_GAMEUPDATE_H
