#ifndef PEKINGEXPRESS_GAME_MODEL_MOVE_H
#define PEKINGEXPRESS_GAME_MODEL_MOVE_H

#include "PekingExpress/Game/Model/Node.h"

namespace PekingExpress
{
	class Move
	{
	private:
		Node* startLocation;
		Node* endLocation;
		const int price;

	public:
		Move(Node* startLocation_, Node* endLocation_, int price_);
		~Move();
	public:
		Node* GetStartLocation() const;
		Node* GetEndLocation() const;
		const int GetPrice() const;
	};
}

#endif //PEKINGEXPRESS_GAME_MODEL_MOVE_H