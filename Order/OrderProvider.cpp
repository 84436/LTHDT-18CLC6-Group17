#include "OrderProvider.h"

int32_t OrderProvider::NewOrderIDCounter = 0;

bool OrderProvider::isNotPending_Buyer(Order _Order)
{
	int8_t Status = OrderProvider::GetInstance().GetByID(_Order.ID())->Status();
	return (Status == BUYER_CANCELLED) || (Status == SELLER_CANCELLED) || (Status == COMPLETED);
}

bool OrderProvider::isNotPending_Seller(Order _Order)
{
	int8_t Status = OrderProvider::GetInstance().GetByID(_Order.ID())->Status();
	return (Status != SELLER_PENDING);
}

bool OrderProvider::isNotPending_Shipper(Order _Order)
{
	int8_t Status = OrderProvider::GetInstance().GetByID(_Order.ID())->Status();
	return (Status != SHIPPING_PENDING);
}

bool OrderProvider::isRelated(string _AccountID, string _OrderID)
{
	list<Order> FilteredOrders = OrderProvider::GetInstance().ListByAccountID(_AccountID);
	bool MatchFound = false;
	for (auto i = FilteredOrders.begin(); i != FilteredOrders.end(); ++i)
	{
		if (i->ID() == _OrderID)
		{
			MatchFound = true;
			break;
		}
	}
	return MatchFound;
}

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
	NewOrderIDCounter++;
	size_t NewID_CurrentLength = NewID.length();

	if (NewID_CurrentLength < 4)
		for (size_t i = 0; i < 4 - NewID_CurrentLength; i++)
			NewID.insert(NewID.begin(), '0');
	NewID.insert(NewID.begin(), 'O');

	return NewID;
}

void OrderProvider::ReadFile()
{
	fstream f;
	f.open(DATABASE_PATH, fstream::in);
	if (!f.is_open() || f.peek() == fstream::traits_type::eof())
	{
		cout << "Database either is inaccessible or does not exist." << endl;
		exit(-1);
	}
	json File = json::parse(f);

	// Orders
	for (auto i = File["ORDERS"].begin(); i != File["ORDERS"].end(); ++i)
	{
		Order _Order;
		_Order.ID(i.key());
		_Order.ProductID((*i)["ProductID"]);
		_Order.SellerID((*i)["SellerID"]);
		_Order.BuyerID((*i)["BuyerID"]);
		_Order.ShipperID((*i)["ShipperID"]);
		_Order.PriceCoeff((*i)["PriceCoeff"]);
		_Order.ShippingFee((*i)["ShippingFee"]);
		_Order.OrderDate(Date{ (*i)["OrderDate"][0], (*i)["OrderDate"][1], (*i)["OrderDate"][2] });
		_Order.ShippingDate(Date{ (*i)["ShippingDate"][0], (*i)["ShippingDate"][1], (*i)["ShippingDate"][2] });
		_Order.Status((*i)["Status"]);
		_Order.Note((*i)["Note"]);
		_Order.Quantity((*i)["Quantity"]);
		Orders.push_back(_Order);
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
	f << setw(4) << File;

	f.close();
}

void OrderProvider::Add(Order _Order)
{
	_Order.ID(OrderProvider::GenerateNewOrderID());
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

list<Order> OrderProvider::ListByAccountID(string _AccountID)
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
