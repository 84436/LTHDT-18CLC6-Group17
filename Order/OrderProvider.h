#pragma once
#include "../_INCLUDES_.h"

class OrderProvider : public Provider
{
	private:
		list<Order> Orders;

	public:
		void Add(Product _Product);
		void Delete(string _ID);
		Product* GetByID(string _ID);
		list<Product> Search(string _Name);
		list<Product> Search(Seller* _Seller);
};
