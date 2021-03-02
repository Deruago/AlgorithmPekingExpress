#ifndef PEKINGEXPRESS_GAME_MODEL_COUPLE_H
#define PEKINGEXPRESS_GAME_MODEL_COUPLE_H

namespace PekingExpress
{
	class Node;

	class Couple
	{
	public:
		Couple() = default;
		~Couple() = default;

		Node* GetCurrentPosition() const;
	public:
		Node* currentPosition = nullptr;
	};
}

#endif //PEKINGEXPRESS_GAME_MODEL_COUPLE_H