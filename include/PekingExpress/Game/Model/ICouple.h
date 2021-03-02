#ifndef PEKINGEXPRESS_GAME_MODEL_ICOUPLE_H
#define PEKINGEXPRESS_GAME_MODEL_ICOUPLE_H

#include "PekingExpress/Game/Model/Node.h"

namespace PekingExpress
{
	class ICouple
	{
	public:
		ICouple() = default;
		virtual ~ICouple() = default;
	public:
		virtual Node* GetCurrentPosition() const = 0;
		virtual int GetBudget() const = 0;
		virtual int GetId() const = 0;

		virtual void SetCurrentPosition(Node* const node) = 0;
		virtual void SetBudget(const int newBudget) = 0;
	};
}

#endif //PEKINGEXPRESS_GAME_MODEL_ICOUPLE_H