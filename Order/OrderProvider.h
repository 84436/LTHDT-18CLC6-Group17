#pragma once
#include "../_INCLUDES_.h"
#include "../Account/AccountProvider.h"
#include "../Product/ProductProvider.h"
#include "Order.h"

class OrderProvider
{
	private:
		OrderProvider();
	public:
		static OrderProvider& GetInstance();

	private:
		list<Order> Orders;
		AccountProvider* _AccountProvider;
		ProductProvider* _ProductProvider;
		static int64_t NewOrderIDCounter;
		string GenerateNewOrderID();

	public:
		void SetAccountProvider(AccountProvider* _AccountProvider);
		void SetProductProvider(ProductProvider* _ProductProvider);

		void ReadFile();
		void WriteFile();
		void Add(Order _Order);
		void Delete(string _ID);
		Order* GetByID(string _ID);
		/*list<Order> Search(Buyer* _Buyer);
		list<Order> Search(Seller* _Seller);
		list<Order> Search(Shipper* _Shipper);*/
};
