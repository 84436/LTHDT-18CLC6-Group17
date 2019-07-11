#pragma once
#include "_INCLUDES_.h"

class Seller : public Person {
	private:
		int Rating[5];
		vector <Shipper> Shippers;

	public:
		Seller() : Person() {}

		void ListProduct();
		void CreateProduct();
		void EditProduct(Product);
};
