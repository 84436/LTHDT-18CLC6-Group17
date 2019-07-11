#pragma once
#include "_INCLUDES_.h"

class Shipper : public Person {
	private:
	public:
		Shipper() : Person() {};

		void setShippingFee(uint64_t);
		void updateStatus(uint8_t);
};
