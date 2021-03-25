#include <iostream>
#include "PekingExpress/Game/Init/JsonToGraph.h"
#include "PekingExpress/Game/Update/GameUpdate.h"
#include <fstream>

#include "PekingExpress/Game/Init/JsonToArray.h"

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

enum class Test
{
	one,
	two,
	three,
	four,
};

PekingExpress::Graph* GetGraph(Test testType)
{
	std::ifstream input;
	std::string filePath;
	switch(testType)
	{
	case Test::one:
		filePath = "./data1.json";
		break;
	case Test::two:
		filePath = "./data2.json";
		break;
	case Test::three:
		filePath = "./data3.json";
		break;
	case Test::four:
		filePath = "./data4.json";
		break;
	}
	input.open(filePath);

	std::string inputString;
	std::string line;

	while (getline(input, line))
	{
		inputString += line;
		line.clear();
	}
	input.close();
	
	PekingExpress::JsonToGraph graph;
	
	return graph.ConvertJsonToGraph(inputString);
}

std::vector<std::vector<PekingExpress::Node*>> GetOpponentTurns(Test testType, PekingExpress::Graph* graph)
{
	std::ifstream input;
	std::string filePath;
	switch (testType)
	{
	case Test::one:
		filePath = "./opponent1.json";
		break;
	case Test::two:
		filePath = "./opponent2.json";
		break;
	case Test::three:
		filePath = "./opponent3.json";
		break;
	case Test::four:
		filePath = "./opponent4.json";
		break;
	}
	input.open(filePath);

	std::string inputString;
	std::string line;

	while (getline(input, line))
	{
		inputString += line;
		line.clear();
	}
	input.close();

	return PekingExpress::JsonToArray().GetOpponentsMoves(inputString, *graph);
}

void PrintResult(std::vector<PekingExpress::Move*> path, bool win)
{
	std::cout << "\nResults\n";
	if (win)
	{
		std::cout << "You win!\n";
	}
	else
	{
		std::cout << "You lose!\n";
	}
	std::cout << "Path taken:\n";
	for (auto* i : path)
	{
		std::cout << "\tStart: " << i->GetStartLocation()->GetId() << " End: " << i->GetEndLocation()->GetId() << "\n";
	}

	std::cout << '\n';
}

int main()
{
	const Test TestType = Test::four;
	
	std::cout << "Input startlocation: ";
	int startlocation = 0;
	std::cin >> startlocation;
	
	std::cout << "Input budget: ";
	int budget = 0;
	std::cin >> budget;
	
	auto* newGraph = GetGraph(TestType);

	auto couple1 = new PekingExpress::Couple(budget, 1, newGraph->GetNode(startlocation));

	PekingExpress::GameUpdate gameUpdate(newGraph, couple1, { 0 });

	auto opponentsMove = GetOpponentTurns(TestType, newGraph);

	std::vector<PekingExpress::Move*> path;

	int currentLocation = 0;

	bool win = false;

	while (true)
	{
		auto* move = gameUpdate.NextMove();
		//std::cout << "Current move from: " << move->GetStartLocation()->GetId() << " To: " << move->GetEndLocation()->GetId() << '\n';
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
		if ((currentLocation + 1) < opponentsMove.size())
		{
			currentLocation += 1;
		}
	}

	PrintResult(path, win);
}
