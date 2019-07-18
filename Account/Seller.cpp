#include "Seller.h"

vector<uint16_t> Seller::RatingArray()
{
	return Rating;
}

void Seller::RatingArray(uint16_t _1, uint16_t _2, uint16_t _3, uint16_t _4, uint16_t _5)
{
	this->Rating[0] = _1;
	this->Rating[1] = _2;
	this->Rating[2] = _3;
	this->Rating[3] = _4;
	this->Rating[4] = _5;
}
