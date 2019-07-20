#include "ProductProvider.h"

int32_t ProductProvider::NewProductIDCounter = 0;

ProductProvider::ProductProvider()
{
	ReadFile();
}

ProductProvider& ProductProvider::GetInstance()
{
	static ProductProvider Instance;
	return Instance;
}

string ProductProvider::GenerateNewProductID()
{
	string NewID = to_string(NewProductIDCounter);

	if (NewID.length() < 8)
		for (size_t i = 0; i < 8 - NewID.length(); i++)
			NewID.insert(NewID.begin(), '0');
	NewID.insert(NewID.begin(), 'P');

	return NewID;
}

void ProductProvider::ReadFile()
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

	// Products
	for (auto i = File["PRODUCTS"].begin(); i != File["PRODUCTS"].end(); ++i)
	{
		Product p;
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

	// New ID counter
	NewProductIDCounter = File["COUNTERS"]["PRODUCT"];
}

void ProductProvider::WriteFile()
{
	fstream f(DATABASE_PATH, fstream::out | fstream::trunc);
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
	ReadFile();
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

list<Product> ProductProvider::SearchByName(string _Name, bool _isR18)
{
	list<Product> _Products;
	for (auto i = Products.begin(); i != Products.end(); ++i)
	{
		if ((ToLower(i->Name()).find(ToLower(_Name)) != string::npos) && (i->isR18() == _isR18 ))
		{
			_Products.push_back((*i));
		}
	}
	return _Products;
}

list<Product> ProductProvider::SearchBySeller(string _SellerID, bool _isR18)
{
	list<Product> _Products;
	for (auto i = Products.begin(); i != Products.end(); ++i)
	{
		if (i->SellerID() == _SellerID && (i->isR18() == _isR18))
		{
			_Products.push_back((*i));
		}
	}
	return _Products;
}
