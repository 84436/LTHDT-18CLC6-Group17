#pragma once
#include "../_INCLUDES_.h"

class Seller : public Account {
	private:
		vector<uint16_t> Rating = { 0, 0, 0, 0, 0 };

	public:
		Seller() : Account() {}

		vector<uint16_t> RatingArray();
		void RatingArray(uint16_t _1, uint16_t _2, uint16_t _3, uint16_t _4, uint16_t _5);
};
