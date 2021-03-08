#include "PekingExpress/Game/Model/Couple.h"

PekingExpress::Couple::Couple(int budget_, int id_, Node* const startPostion_)
	:	currentPosition(startPostion_),
		budget(budget_),
		id(id_)
{
}

PekingExpress::Node* PekingExpress::Couple::GetCurrentPosition() const
{
	return currentPosition;
}

int PekingExpress::Couple::GetBudget() const
{
	return budget;
}

int PekingExpress::Couple::GetId() const
{
	return id;
}

void PekingExpress::Couple::SetCurrentPosition(Node* const node)
{
	currentPosition = node;
}

void PekingExpress::Couple::SetBudget(const int newBudget)
{
	budget = newBudget;
}
