#pragma once
#include "../_INCLUDES_.h"

class Database
{
	private:
		static Database* Instance;
		Database();
	public:
		static Database* GetInstance();

	private:
		json File;
		void Initialize();
		void ReadFile();
		void WriteFile();
	public:
		list<Account*> GetAccounts();
		list<Product> GetProducts();
		list<Order> GetOrders();
		void Update(list<Account*> a);
		void Update(list<Product> p);
		void Update(list<Order> o);
};
