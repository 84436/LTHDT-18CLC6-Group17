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
	fstream f;
	f.open(DATABASE_PATH, fstream::in);
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
		o.ShippingFee((*i)["ShippingFee"]);
		o.OrderDate(Date{ (*i)["OrderDate"][0], (*i)["OrderDate"][1], (*i)["OrderDate"][2] });
		o.ShippingDate(Date{ (*i)["ShippingDate"][0], (*i)["ShippingDate"][1], (*i)["ShippingDate"][2] });
		o.Status((*i)["Status"]);
		o.Note((*i)["Note"]);
		o.Quantity((*i)["Quantity"]);
		Orders.push_back(o);
	}

	// New ID counter
	NewOrderIDCounter = File["COUNTERS"]["ORDER"];

	f.close();
}

void OrderProvider::WriteFile()
{
	// Parse existing file
	fstream f;
	f.open(DATABASE_PATH, fstream::in);
	if (
		!f.is_open()
		|| f.peek() == fstream::traits_type::eof()
		)
	{
		cout << "Database does not exist." << endl;
		return;
	}
	json File = json::parse(f);

	// Re-write the relevant object
	File["ORDERS"].clear();
	for (auto i = Orders.begin(); i != Orders.end(); ++i)
	{
		File["ORDERS"].push_back(json::object_t::value_type(
			{
				i->ID(),
				{
					{"ProductID", i->ProductID()},
					{"BuyerID", i->BuyerID()},
					{"SellerID", i->SellerID()},
					{"ShipperID", i->ShipperID()},
					{"PriceCoeff", i->PriceCoeff()},
					{"ShippingFee", i->ShippingFee()},
					{"OrderDate",
						{
							i->OrderDate().Day,
							i->OrderDate().Month,
							i->OrderDate().Year
						}
					},
					{"ShippingDate",
						{
							i->ShippingDate().Day,
							i->ShippingDate().Month,
							i->ShippingDate().Year
						}
					},
					{"Status", i->Status()},
					{"Note", i->Note()},
					{"Quantity", i->Quantity()},
				}
			}
		));
	}

	// Re-write relevant keys
	File["COUNTERS"]["ORDER"] = NewOrderIDCounter;
	
	// Re-write the file
	f.close();
	f.open(DATABASE_PATH, fstream::out | fstream::trunc);
	f << File;

	f.close();
}

void OrderProvider::Add(Order _Order)
{
	Order x = _Order;
	x.ID(OrderProvider::GenerateNewOrderID());
	Orders.push_back(x);
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