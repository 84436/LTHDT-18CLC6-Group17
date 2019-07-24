#pragma once
#include "../_INCLUDES_.h"
#include "Order.h"

class OrderProvider
{
	private:
		OrderProvider();
		~OrderProvider() {}
	public:
		static OrderProvider& GetInstance();

	private:
		list<Order> Orders;
		static int32_t NewOrderIDCounter;
		string GenerateNewOrderID();

	public:
		static bool isCompleted(Order _Order);
		static bool isNotSellerPending(Order _Order);
		static bool isNotShipperPending(Order _Order);
		static bool isRelated(string _AccountID, string _OrderID);

		void ReadFile();
		void WriteFile();

		void Add(Order _Order);
		void Delete(string _ID);
		Order* GetByID(string _OrderID);
		list<Order> ListByAccountID(string _AccountID);
};
