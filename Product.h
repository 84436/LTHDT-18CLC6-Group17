#pragma once
#include "_INCLUDES_.h"

class Product {
	private:
		Seller* Provider;
		string ID;
		string Name;
		string Category;
		string Decription;
		uint32_t Stock;
		uint64_t Price;
		uint64_t ShippingFee;
		int Rating[5] = {0};

	public:
		void GetInfo();
		void Rate(int);
		uint64_t getPrice();
		uint64_t getShippingFee();
		void setShippingFee(uint64_t);
};
