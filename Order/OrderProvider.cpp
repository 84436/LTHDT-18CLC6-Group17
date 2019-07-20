#include "OrderProvider.h"

int32_t OrderProvider::NewOrderIDCounter = 0;

OrderProvider::OrderProvider()
{
	ReadFile();
}

OrderProvider& OrderProvider::GetInstance()
{
	static OrderProvider Instance;
	return Instance;
}

string OrderProvider::GenerateNewOrderID()
{
	string NewID = to_string(NewOrderIDCounter);

	if (NewID.length() < 8)
		for (size_t i = 0; i < 8 - NewID.length(); i++)
			NewID.insert(NewID.begin(), '0');
	NewID.insert(NewID.begin(), 'O');

	return NewID;
}

void OrderProvider::ReadFile()
{
	fstream f(DATABASE_PATH, fstream::in);
	if (
		!f.is_open()
		|| f.peek() == fstream::traits_type::eof()
		)
	{
		cout << "Database does not exist." << endl;
		return;
	}
	json File = json::parse(f);

	// Orders
	for (auto i = File["ORDERS"].begin(); i != File["ORDERS"].end(); ++i)
	{
		Order o;
		o.ID(i.key());
		o.ProductID((*i)["ProductID"]);
		o.SellerID((*i)["SellerID"]);
		o.BuyerID((*i)["BuyerID"]);
		o.ShipperID((*i)["ShipperID"]);
		o.PriceCoeff((*i)["PriceCoeff"]);
		o.ShippingFee((*i)["PriceCoeff"]);
		// o.OrderDate((*i) ...);
		// o.ShippingDate((*i) ...);
		o.Status((*i)["Status"]);
		o.Note((*i)["Note"]);
		Orders.push_back(o);
	}

	// New ID counter
	NewOrderIDCounter = File["COUNTERS"]["ORDER"];
}

void OrderProvider::WriteFile()
{
	fstream f(DATABASE_PATH, fstream::out | fstream::trunc);
	if (
		!f.is_open()
		|| f.peek() == fstream::traits_type::eof()
		) {
		return;
	}
	json File = json::parse(f);
	File["ORDERS"].clear();
	for (auto i = Orders.begin(); i != Orders.end(); ++i)
	{
		File["ORDERS"].push_back(json::object_t::value_type(
			{
				i->ID(),
				{
					{"BuyerID", i->BuyerID()}
					//{"SellerID", (i->SellerID() == nullptr ? "NULL" : i->SellerID()},
					//{"isR18", i->isR18()},
					//{"Name", i->Name()},
					//{"Category", i->Category()},
					//{"Description", i->Description()},
					//{"Stock", i->Stock()},
					//{"Price", i->Price()}
				}
			}
		));
	}
	f << File;
	ReadFile();
}

void OrderProvider::Add(Order _Order)
{
	Orders.push_back(_Order);
}

void OrderProvider::Delete(string _ID)
{
	for (auto i = Orders.begin(); i != Orders.end(); ++i)
	{
		if (ToLower(i->ID()) == ToLower(_ID))
		{
			Orders.erase(i);
			break;
		}
	}
}

Order* OrderProvider::GetByID(string _OrderID)
{
	Order* _Order = nullptr;
	for (auto i = Orders.begin(); i != Orders.end(); ++i)
	{
		if (ToLower(i->ID()) == ToLower(_OrderID))
		{
			_Order = &(*i);
		}
	}
	return _Order;
}

list<Order> OrderProvider::Search(string _AccountID)
{
	list<Order> FilteredOrders;

	if (_AccountID[0] == 'B') {
		for (auto i = Orders.begin(); i != Orders.end(); ++i)
		{
			if (i->BuyerID() == _AccountID)
				FilteredOrders.push_back(*i);
		}
	}
	
	if (_AccountID[0] == 'S') {
		for (auto i = Orders.begin(); i != Orders.end(); ++i)
		{
			if (i->SellerID() == _AccountID)
				FilteredOrders.push_back(*i);
		}
	}

	if (_AccountID[0] == 'H') {
		for (auto i = Orders.begin(); i != Orders.end(); ++i)
		{
			if (i->ShipperID() == _AccountID)
				FilteredOrders.push_back(*i);
		}
	}

	return FilteredOrders;
}