#pragma once
#include "../_INCLUDES_.h"
#include "Account.h"

class Buyer : public Account
{
	public:
		Buyer() : Account() {};
		Buyer(const Buyer& b) : Account(b) {};

		void SearchProductByID(string _ProductID);
		void SearchProductByName(string _ProductName);
		void CreateOrder(); //
		void CancelOrder(string _OrderID); //
		void Rate(string _OrderID);
};
