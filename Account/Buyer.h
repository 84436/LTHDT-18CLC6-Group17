#pragma once
#include "../_INCLUDES_.h"

class Buyer : public Account {
	private:
		

	public:
		Buyer() : Account() {};

		void SearchProduct();
		Order CreateOrder();
		void CancelOrder(Order& _order);
		void Rate(Order& _order);
};
