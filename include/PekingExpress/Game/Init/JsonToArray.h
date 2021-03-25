#ifndef JSONTOARRAY_H
#define JSONTOARRAY_H
#include "json/reader.h"
#include "PekingExpress/Game/Model/Node.h"
#include <iostream>

namespace PekingExpress
{
	class JsonToArray
	{
	public:
		Json::Reader reader;

		JsonToArray() = default;
		~JsonToArray() = default;

		std::vector<std::vector<PekingExpress::Node*>> GetOpponentsMoves(const std::string& json, Graph& graph)
		{
			Json::Value value;
			reader.parse(json, value);
			std::vector<std::vector<PekingExpress::Node*>> turns;
			
			for (auto item : value)
			{
				std::vector<PekingExpress::Node*> tmp;
				for (auto element : item)
				{
					tmp.push_back(graph.GetNode(element.asInt()));
				}
				turns.push_back(tmp);
			}
			
			return turns;
		}
	};
}

#endif //JSONTOARRAY_H