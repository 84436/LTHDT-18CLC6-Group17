#include "Database.h"

Database* Database::Instance = nullptr;

Database* Database::GetInstance()
{
	if (Instance == nullptr) Instance = new Database;
	return Instance;
}

void Database::Initialize()
{
	File =
	{
		{"ACCOUNTS", {}},
		{"PRODUCTS", {}},
		{"ORDERS", {}}
	};
}

void Database::ReadFile()
{
	fstream f(DATABASE_PATH, fstream::in);
	if (
		// File not opened
		!f.is_open()
		// File is empty
		|| f.peek() == fstream::traits_type::eof()
		) { return; }

	File = json::parse(f);
	if (File == json()) {
		Initialize();
		WriteFile();
	}
}

void Database::WriteFile()
{
	fstream f(DATABASE_PATH, fstream::out | fstream::trunc);
	if (!f.is_open()) { return; }
	f << File;
}

list<Account*> Database::GetAccounts()
{
	list<Account*> Accounts;
	for (auto i = File["ACCOUNTS"].begin(); i != File["ACCOUNTS"].end(); ++i)
	{
		/*Account* a;
		if ((*i)["type"] = "Buyer")
		{
			a = new Buyer(i.key(), (*i)["attribute"], ...);
			Accounts.push_back(a);
			continue;
		}
		if ((*i)["type"] = "Seller")
		{
			a = new Seller(i.key(), (*i)["attribute"], ...);
			Accounts.push_back(a);
			continue;
		}if ((*i)["type"] = "Shipper")
		{
			a = new Shipper(i.key(), (*i)["attribute"], ...);
			Accounts.push_back(a);
			continue;
		}*/
	}
	return Accounts;
}

list<Product> Database::GetProducts()
{
	list<Product> Products;
	for (auto i = File["PRODUCTS"].begin(); i != File["PRODUCTS"].end(); ++i)
	{
		// Products.emplace(Products.end(), i.key(), (*i)["attribute"], ...);
	}
	return Products;
}

list<Order> Database::GetOrders()
{
	list<Order> Orders;
	for (auto i = File["ORDERS"].begin(); i != File["ORDERS"].end(); ++i)
	{
		// Orders.emplace(Orders.end(), i.key(), (*i)["attribute"], ...);
	}
	return Orders;
}

void Database::Update(list<Account*> a)
{
	File["ACCOUNTS"].clear();
	for (auto i = a.begin(); i != a.end(); ++i)
	{
		/*File["ACCOUNTS"].push_back(json::object_t::value_type(
			{
				i->GetID(),
				{
					{"attribute", "value"},
				}
			}
		));*/
	}
	WriteFile();
}

void Database::Update(list<Product> p)
{
	File["PRODUCTS"].clear();
	for (auto i = p.begin(); i != p.end(); ++i)
	{
		/*File["PRODUCTS"].push_back(json::object_t::value_type(
			{
				i->GetID(),
				{
					{"attribute", "value"},
				}
			}
		));*/
	}
	WriteFile();
}

void Database::Update(list<Order> o)
{
	File["ORDERS"].clear();
	for (auto i = o.begin(); i != o.end(); ++i)
	{
		/*File["ORDERS"].push_back(json::object_t::value_type(
			{
				i->GetID(),
				{
					{"attribute", "value"},
				}
			}
		));*/
	}
	WriteFile();
}
