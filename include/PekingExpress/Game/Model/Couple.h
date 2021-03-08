#ifndef PEKINGEXPRESS_GAME_MODEL_COUPLE_H
#define PEKINGEXPRESS_GAME_MODEL_COUPLE_H

#include "PekingExpress/Game/Model/ICouple.h"

namespace PekingExpress
{
	class Node;

	class Couple final : public ICouple
	{
	private:
		Node* currentPosition = nullptr;
		int budget = 0;
		int id = 0;
	public:
		Couple(int budget_, int id_, Node* const startPostion_);
		~Couple() override = default;

		Node* GetCurrentPosition() const override;
		int GetBudget() const override;
		int GetId() const override;
		void SetCurrentPosition(Node* const node) override;
		void SetBudget(const int newBudget) override;
	};
}

#endif //PEKINGEXPRESS_GAME_MODEL_COUPLE_H