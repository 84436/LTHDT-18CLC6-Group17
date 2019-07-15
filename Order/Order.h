#pragma once
#include "../_INCLUDES_.h"

struct Date {
	int Day;
	int Month;
	int Year;
};

class Order {
	private:
		string ID;
		Product* Product;
		Seller* Seller;
		Buyer * Buyer;
		Shipper* Shiper;
		float PriceCoeff;
		Date OrderDate;
		Date ShippingDate;
		uint8_t Status;
		string Note;

	public:
		void SetPriceCoeff(float _coeff);
		int64_t getTotalPrice();
		uint8_t getStatus();
		string getNote();
		void setStatus(uint8_t);
		void setNote(string);
};
