#ifndef PEKINGEXPRESS_GAME_INIT_JSONTOGRAPH_H
#define PEKINGEXPRESS_GAME_INIT_JSONTOGRAPH_H

#include "GraphBuilder.h"
#include "json/json.h"

namespace PekingExpress
{
	class JsonToGraph
	{
	private:
		Json::Reader reader;
	public:
		JsonToGraph() = default;
		~JsonToGraph() = default;
	public:
		Graph* ConvertJsonToGraph(const std::string& json);
	};
}

#endif //PEKINGEXPRESS_GAME_INIT_JSONTOGRAPH_H
