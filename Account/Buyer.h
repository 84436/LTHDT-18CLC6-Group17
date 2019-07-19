#pragma once
#include "../_INCLUDES_.h"
#include "Account.h"
#include "AccountProvider.h"
#include "../Product/ProductProvider.h"
#include "..//Order/OrderProvider.h"

class Buyer : public Account {
	private:

	public:
		Buyer() : Account() {};

		void SearchProductByID(string _ProductID);
		void SearchProductByName(string _ProductName);
		/*Order CreateOrder();
		void CancelOrder(Order& _order);*/
		void Rate(string _OrderID);
};
