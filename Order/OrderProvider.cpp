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

void OrderProvider::SetAccountProvider(AccountProvider* _AccountProvider)
{
	this->_AccountProvider = _AccountProvider;
}

void OrderProvider::SetProductProvider(ProductProvider* _ProductProvider)
{
	this->_ProductProvider = _ProductProvider;
}

void OrderProvider::ReadFile()
{
	fstream f(DATABASE_PATH, fstream::in);
	if (
		!f.is_open()
		|| f.peek() == fstream::traits_type::eof()
		) {
		return;
	}
	json File = json::parse(f);

	// Orders
	for (auto i = File["ORDERS"].begin(); i != File["ORDERS"].end(); ++i)
	{
		Order o(_AccountProvider, _ProductProvider);
		o.ID(i.key());
		o.ProductID((*i)["ProductID"]);
		o.SellerID((*i)["SellerID"]);
		o.BuyerID((*i)["BuyerID"]);
		o.ShipperID((*i)["ShipperID"]);
		o.PriceCoeff((*i)["isR18"]);
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
	fstream f(DATABASE_PATH, fstream::in);
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

Order* OrderProvider::GetByID(string _ID)
{
	Order* _Order = nullptr;
	for (auto i = Orders.begin(); i != Orders.end(); ++i)
	{
		if (ToLower(i->ID()) == ToLower(_ID))
		{
			_Order = &(*i);
		}
	}
	return _Order;
}

list<Order*> OrderProvider::Search(Buyer* _Buyer)
{
	list <Order*> FilteredOrders;

	return FilteredOrders;
}

list<Order*> OrderProvider::Search(Seller* _Seller)
{
	list <Order*> FilteredOrders;

	return FilteredOrders;
}

list<Order*> OrderProvider::Search(Shipper* _Shipper)
{
	list <Order*> FilteredOrders;

	return FilteredOrders;
}
