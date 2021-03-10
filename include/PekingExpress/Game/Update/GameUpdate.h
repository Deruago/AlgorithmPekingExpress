#ifndef PEKINGEXPRESS_GAME_UPDATE_GAMEUPDATE_H
#define PEKINGEXPRESS_GAME_UPDATE_GAMEUPDATE_H

#include "PekingExpress/Game/Model/IGraph.h"
#include "PekingExpress/Game/Model/ICouple.h"
#include "PekingExpress/Game/Model/Couple.h"

namespace PekingExpress
{
	class GameUpdate
	{
	private:
		IGraph* graph;
		ICouple* ourCouple;
		std::vector<ICouple*> competitors;

	public:
		GameUpdate(IGraph* graph_, ICouple* ourCouple_, std::vector<ICouple*> competitors_);
		~GameUpdate();

		ICouple* GetCompetitorById(const int id) const;
		std::vector<ICouple*> GetAllCouples();
		IGraph* GetGraph();
		void UpdateBudgetCompetitor(const int id);
		void UpdateBudgetOur();
		void UpdateCompetitorLocation(const int groupid, const int location);
		void UpdateOurLocation(const int location);
		int NextMove();
		void ApplyOurMove(const int location);
	};
}

#endif //PEKINGEXPRESS_GAME_UPDATE_GAMEUPDATE_H
