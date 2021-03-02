#ifndef PEKINGEXPRESS_GAME_MODEL_IGRAPH_H
#define PEKINGEXPRESS_GAME_MODEL_IGRAPH_H

#include "PekingExpress/Game/Model/Node.h"

namespace PekingExpress
{
	class IGraph
	{
	public:
		IGraph() = default;
		~IGraph() = default;
	public:
		virtual const std::vector<Node*> GetLocations() const = 0;
		virtual const std::vector<Node*> GetCriticalLocations() const = 0;
	};
}

#endif //PEKINGEXPRESS_GAME_MODEL_IGRAPH_H