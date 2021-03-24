#ifndef PEKINGEXPRESS_GAME_UPDATE_ALGORITHM_H
#define PEKINGEXPRESS_GAME_UPDATE_ALGORITHM_H

#include "PekingExpress/Game/Model/Node.h"
#include "PekingExpress/Game/Model/Move.h"
#include "PekingExpress/Game/Model/Graph.h"
#include "PekingExpress/Game/Model/Couple.h"
#include <vector>

namespace PekingExpress
{
	class Algorithm
	{
	public:
		Graph* graph = nullptr;

		std::vector<int> dist;
		std::vector<bool> sptSet;
		std::vector<std::pair<int, Node*>> prev;
		std::vector<std::pair<int, Node*>> nodes;

		std::vector<std::pair<int, Node*>> path;
		Couple* ourCouple = nullptr;
	public:
		Algorithm(Graph* graph_);
		~Algorithm() = default;
	public:
		Move* DoAlgorithm();
		std::pair<int, Node*> MinDistance(std::vector<int> dist, std::vector<bool> sptSet, std::vector<std::pair<int, Node*>> nodes);
		std::pair<int, Node*> GetVertex(std::vector<std::pair<int, Node*>> nodes, Connection con);
		bool VertexIsValid(std::pair<int, Node*> v, std::pair<int, Node*> u);
	};
}

#endif //PEKINGEXPRESS_GAME_UPDATE_ALGORITHM_H