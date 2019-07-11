#pragma once
#include "_INCLUDES_.h"

class Buyer : public Person {
	private:
		

	public:
		Buyer() : Person() {};

		void SearchProduct();
		Order CreateOrder();
		void CancelOrder(Order& _order);
		void Rate(Order& _order);
};
