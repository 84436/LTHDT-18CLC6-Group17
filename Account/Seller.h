#pragma once
#include "../_INCLUDES_.h"
#include "Account.h"

class Seller : public Account {
	private:
		vector<int16_t> Rating = { 0, 0, 0, 0, 0 };

	public:
		Seller() : Account() {}

		vector<int16_t> RatingArray();
		void RatingArray(int16_t _1, int16_t _2, int16_t _3, int16_t _4, int16_t _5);
		void Rate(int _score);
};
