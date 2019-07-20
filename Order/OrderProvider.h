#pragma once
#include "../_INCLUDES_.h"
#include "Order.h"

class OrderProvider
{
	private:
		OrderProvider();
	public:
		static OrderProvider& GetInstance();

	private:
		list<Order> Orders;
		static int32_t NewOrderIDCounter;
		string GenerateNewOrderID();

	public:
		void ReadFile();
		void WriteFile();
		void Add(Order _Order);
		void Delete(string _ID);
		Order* GetByID(string _OrderID);
		list<Order> Search(string _AccountID);
};
