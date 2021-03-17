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

		Node* MinDistance(std::vector<int> dist, std::vector<bool> sptSet);
		Connection* GetConnection(Node* startNode, Node* endNode);

	public:
		GameUpdate(Graph* graph_, Couple* ourCouple_, std::vector<Couple*> competitors_);
		~GameUpdate();

		Couple* GetCompetitorById(const int id) const;
		std::vector<Couple*> GetAllCouples() const;
		const Graph* GetGraph() const;
		void UpdateBudgetCompetitor(const int id, int newBudget);
		void UpdateBudgetOur(int newBudget);
		void UpdateOccupiedLocations(std::vector<Node*> nodes);
		void UpdateOurLocation(const int location);
		const int NextMove();
		void ApplyOurMove(const int location);

		void printPath(Node* parent[], int j);
	};
}

#endif //PEKINGEXPRESS_GAME_UPDATE_GAMEUPDATE_H
