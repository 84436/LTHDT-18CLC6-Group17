#pragma once
#include "../_INCLUDES_.h"

class Shipper : public Account {
	private:
	public:
		Shipper() : Account() {};

		void setShippingFee(int64_t);
		void updateStatus(uint8_t);
};
