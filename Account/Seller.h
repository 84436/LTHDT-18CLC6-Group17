#pragma once
#include "../_INCLUDES_.h"

class Seller : public Account {
	private:
		int Rating[5];
		vector <Shipper> Shippers;

	public:
		Seller() : Account() {}

		void ListProduct();
		void CreateProduct();
		void EditProduct(Product);
};
