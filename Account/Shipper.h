#pragma once
#include "../_INCLUDES_.h"
#include "Account.h"

class Shipper : public Account
{
	private:
	public:
		Shipper() : Account() {}
		Shipper(const Shipper& h) : Account(h) {}

		void FinishOrder(string _OrderID);
};
