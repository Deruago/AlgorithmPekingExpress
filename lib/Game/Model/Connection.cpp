#include "PekingExpress/Game/Model/Connection.h"

PekingExpress::Connection::Connection(Node* const node_, const int price_)
	:	Node_(node_),
		Price_(price_)
{
}

const PekingExpress::Node* PekingExpress::Connection::GetNode() const
{
	return Node_;
}

int PekingExpress::Connection::GetPrice() const
{
	return Price_;
}
