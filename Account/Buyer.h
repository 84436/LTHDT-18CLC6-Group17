#pragma once
#include "../_INCLUDES_.h"
#include "Account.h"
#include "../Product/ProductProvider.h"
#include "../Order/Order.h"

class Buyer : public Account {
	private:

	public:
		Buyer() : Account() {};

		void SearchProduct(string _name);
		Order CreateOrder();
		void CancelOrder(Order& _order);
		void Rate(Order& _order);
};
