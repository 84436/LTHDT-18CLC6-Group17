#include "OrderProvider.h"

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
					{"SellerID", i->SellerID()},
					{"isR18", i->isR18()},
					{"Name", i->Name()},
					{"Category", i->Category()},
					{"Description", i->Description()},
					{"Stock", i->Stock()},
					{"Price", i->Price()}
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
