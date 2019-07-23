#pragma once
#include "../_INCLUDES_.h"
#include "Account.h"

class Buyer : public Account
{
	public:
		Buyer() : Account() {}
		Buyer(const Buyer& b) : Account(b) {}

		void ListOrder_Pending();
		void AddOrder(string _ProductID);
		void CancelOrder(string _OrderID);

		void SearchProductByID(string _ProductID);
		void SearchProductBySellerID(string _SellerID);
		void SearchProductByQuery(string _ProductName);
		
		void Rate(string _OrderID);
};
