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

	for (auto* node : newGraph->GetLocations())
	{
		std::cout << node->GetId() << " " << std::endl;
	}
	
	PekingExpress::GameUpdate gameUpdate(newGraph, couple1, { couple2 });

	std::vector<PekingExpress::Move*> path;
	//std::vector<int> path;

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
		auto* move = gameUpdate.NextMove();
		std::cout << "Current move from: " << move->GetStartLocation()->GetId() << " To: " << move->GetEndLocation()->GetId() << '\n';
		path.push_back(move);
		gameUpdate.ApplyOurMove(move);

		std::vector<PekingExpress::Node*> occupiedNodes;
		for (auto* opponentOccupy : opponentsMove[currentLocation])
		{
			occupiedNodes.push_back(opponentOccupy);
		}
		occupiedNodes.push_back(move->GetEndLocation());
		
		gameUpdate.UpdateOccupiedLocations(occupiedNodes);
		if (move->GetEndLocation()->GetId() == PekingExpress::Graph::GoalId())
		{
			win = true;
			break;
		}
		else if (OpponentsAtEnding(opponentsMove, currentLocation))
		{
			win = false;
			break;
		}
		
		currentLocation += 1;
	}

	std::cout << "Path taken:\n";
	for (auto* i : path)
	{
		std::cout << "Start: " << i->GetStartLocation()->GetId() << " End: " << i->GetEndLocation()->GetId() << "\n";
	}


	std::cout << '\n';
}
