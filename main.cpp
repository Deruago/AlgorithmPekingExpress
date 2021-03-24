#include <iostream>
#include "PekingExpress/Game/Init/JsonToGraph.h"
#include "PekingExpress/Game/Update/GameUpdate.h"
#include <fstream>

bool OpponentsAtEnding(const std::vector<std::vector<PekingExpress::Node*>>& vector, int currentLocation)
{
	for (auto* i : vector[currentLocation])
	{
		if (i->GetId() == 88)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	std::ifstream input;
	input.open("./data.json");
	
	std::string inputString;
	std::string line;

	while (getline(input, line))
	{
		inputString += line;
	}

	std::cout << "Input startlocation: ";
	int startlocation = 0;
	std::cin >> startlocation;
	
	std::cout << "Input budget: ";
	int budget = 0;
	std::cin >> budget;
	
	PekingExpress::JsonToGraph graph;
	auto* newGraph = graph.ConvertJsonToGraph(inputString);

	auto couple1 = new PekingExpress::Couple(budget, 1, newGraph->GetNode(startlocation));
	auto couple2 = new PekingExpress::Couple(budget, 2, newGraph->GetNode(startlocation));

	PekingExpress::GameUpdate gameUpdate(newGraph, couple1, { couple2 });

	//std::vector<PekingExpress::Move*> path;
	std::vector<int> path;

	std::vector<std::vector<PekingExpress::Node*>> opponentsMove = {
		{
			newGraph->GetNodes({2, 3})
		},
		{
			newGraph->GetNodes({3})
		},
		{
			newGraph->GetNodes({88})
		},
		{
			newGraph->GetNodes({88})
		}
	};

	int currentLocation = 0;

	bool win = false;
	
	while (true)
	{
		auto move = gameUpdate.NextMove();
		path.push_back(move);
		gameUpdate.ApplyOurMove(move);
		if (gameUpdate.CanOpponentMove(opponentsMove[currentLocation + 1]))
		{
			if ((currentLocation + 1) < opponentsMove.size())
			{
				currentLocation += 1;			
			}
		}
		
		gameUpdate.UpdateOccupiedLocations({ opponentsMove[currentLocation], move });
		if (move == 88)
		{
			win = true;
			break;
		}
		else if (OpponentsAtEnding(opponentsMove, currentLocation))
		{
			win = false;
			break;
		}
	}

	std::cout << "Path taken:\n";
	for (auto i : path)
	{
		std::cout << i << " ";
	}

	std::cout << '\n';
}
