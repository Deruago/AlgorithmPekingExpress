#include "PekingExpress/Game/Model/Move.h"

PekingExpress::Move::Move(Node* startLocation_, Node* endLocation_, int price_)
	: startLocation(startLocation_),
	  endLocation(endLocation_),
	  price(price_)
{
}

const PekingExpress::Node* PekingExpress::Move::GetStartLocation() const
{
	return startLocation;
}

const PekingExpress::Node* PekingExpress::Move::GetEndLocation() const
{
	return endLocation;
}

const int PekingExpress::Move::GetPrice() const
{
	return price;
}

PekingExpress::Move::~Move()
{
}