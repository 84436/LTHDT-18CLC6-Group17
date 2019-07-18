#include "ProductProvider.h"

void ProductProvider::SetAccountProvider(AccountProvider* _AccountProvider)
{
	this->_AccountProvider = _AccountProvider;
}

void ProductProvider::ReadFile()
{
	fstream f(DATABASE_PATH, fstream::in);
	if (
		!f.is_open()
		|| f.peek() == fstream::traits_type::eof()
		) {
		return;
	}
	json File = json::parse(f);
	for (auto i = File["PRODUCTS"].begin(); i != File["PRODUCTS"].end(); ++i)
	{
		Product p(_AccountProvider);
		p.ID(i.key());
		p.SellerID((*i)["SellerID"]);
		p.isR18((*i)["isR18"]);
		p.Name((*i)["Name"]);
		p.Category((*i)["Category"]);
		p.Description((*i)["Description"]);
		p.Stock((*i)["Stock"]);
		p.Price((*i)["Price"]);
		Products.push_back(p);
	}
}

void ProductProvider::WriteFile()
{
	fstream f(DATABASE_PATH, fstream::in);
	if (
		!f.is_open()
		|| f.peek() == fstream::traits_type::eof()
		) {
		return;
	}
	json File = json::parse(f);
	File["PRODUCTS"].clear();
	for (auto i = Products.begin(); i != Products.end(); ++i)
	{
		File["PRODUCTS"].push_back(json::object_t::value_type(
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

void ProductProvider::Add(Product _Product)
{
	Products.push_back(_Product);
}

void ProductProvider::Delete(string _ID)
{
	for (auto i = Products.begin(); i != Products.end(); ++i)
	{
		if (ToLower(i->ID()) == ToLower(_ID))
		{
			Products.erase(i);
			break;
		}
	}
}

Product* ProductProvider::GetByID(string _ID)
{
	Product* _Product = nullptr;
	for (auto i = Products.begin(); i != Products.end(); ++i)
	{
		if (ToLower(i->ID()) == ToLower(_ID))
		{
			_Product = &(*i);
		}
	}
	return _Product;
}

list<Product> ProductProvider::SearchByName(string _Name)
{
	list<Product> _Products;
	for (auto i = Products.begin(); i != Products.end(); ++i)
	{
		if (ToLower(i->Name()).find(ToLower(_Name)) != string::npos)
		{
			_Products.push_back((*i));
		}
	}
	return _Products;
}

list<Product> ProductProvider::SearchBySeller(string _SellerID)
{
	list<Product> _Products;
	for (auto i = Products.begin(); i != Products.end(); ++i)
	{
		if (i->SellerID() == _SellerID)
		{
			_Products.push_back((*i));
		}
	}
	return _Products;
}
