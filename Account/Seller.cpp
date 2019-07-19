#include "Seller.h"

vector<int16_t> Seller::RatingArray()
{
	return Rating;
}

void Seller::RatingArray(int16_t _1, int16_t _2, int16_t _3, int16_t _4, int16_t _5)
{
	this->Rating[0] = _1;
	this->Rating[1] = _2;
	this->Rating[2] = _3;
	this->Rating[3] = _4;
	this->Rating[4] = _5;
}

void Seller::Rate(int _score)
{
	Rating[_score - 1]++;
}
