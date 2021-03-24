#ifndef PEKINGEXPRESS_GAME_MODEL_GRAPH_H
#define PEKINGEXPRESS_GAME_MODEL_GRAPH_H

#include "PekingExpress/Game/Model/IGraph.h"

namespace PekingExpress
{
	class Graph final : public IGraph
	{
	private:
		std::vector<Node*> locations;
	public:
		Graph(std::vector<Node*> locations_);
		~Graph() override;

		/*! \fn GetLocations
		 *
		 *	\brief Get all locations that are in this graph.
		 */
		const std::vector<Node*> GetLocations() const override;
		PekingExpress::Node* GetNode(int id) const;
		std::vector<PekingExpress::Node*> GetNodes(const std::vector<int>& ids) const;

		/*!	\fn GetCriticalLocations
		 *
		 *	\brief Get all critical locations found in the graph.
		 *
		 *	\details It loops through the locations, and returns a new vector with critical locations.
		 */
		const std::vector<Node*> GetCriticalLocations() const override;

		constexpr static int GoalId()
		{
			return 88;
		}
	};
}

#endif //PEKINGEXPRESS_GAME_MODEL_GRAPH_H