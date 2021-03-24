#ifndef PEKINGEXPRESS_GAME_INIT_IGRAPHBUILDER_H
#define PEKINGEXPRESS_GAME_INIT_IGRAPHBUILDER_H

#include "PekingExpress/Game/Model/Node.h"
#include "PekingExpress/Game/Model/IGraph.h"
#include "PekingExpress/Game/Model/Connection.h"

namespace PekingExpress
{
	class IGraphBuilder
	{
	public:
		IGraphBuilder() = default;
		virtual ~IGraphBuilder() = default;
	public:
		virtual void AddNode(int nodeId, bool isCritical) = 0;
		virtual void AddCriticalNode(int nodeId) = 0;
		virtual void AddConnection(int sourceNode, int destinationNode, int price) = 0;
		virtual IGraph* GetGraph() const = 0;
	};
}

#endif //PEKINGEXPRESS_GAME_INIT_IGRAPHBUILDER_H