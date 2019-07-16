#include "ProductProvider.h"

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

list<Product> ProductProvider::Search(string _Name)
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

list<Product> ProductProvider::Search(Seller* _Seller)
{
	list<Product> _Products;
	for (auto i = Products.begin(); i != Products.end(); ++i)
	{
		if (i->SellerID() = _Seller.ID())
		{
			_Products.push_back((*i));
		}
	}
	return _Products;
}
