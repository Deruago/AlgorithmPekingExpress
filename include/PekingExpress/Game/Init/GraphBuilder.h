#ifndef PEKINGEXPRESS_GAME_INIT_GRAPHBUILDER_H
#define PEKINGEXPRESS_GAME_INIT_GRAPHBUILDER_H

#include "PekingExpress/Game/Init/IGraphBuilder.h"
#include "PekingExpress/Game/Model/Graph.h"

namespace PekingExpress
{
	class GraphBuilder final : public IGraphBuilder
	{
	private:
		std::vector<Node*> graphNodes;
	public:
		GraphBuilder();
		~GraphBuilder();
	public:
		void AddNode(int nodeId);
		void AddCriticalNode(int nodeId);
		void AddConnection(int sourceNode, int destinationNode, int price);
		Graph* GetGraph() const;
	};
}

#endif //PEKINGEXPRESS_GAME_INIT_IGRAPHBUILDER_H