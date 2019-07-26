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
	size_t NewID_CurrentLength = NewID.length();

	if (NewID_CurrentLength < 4)
		for (size_t i = 0; i < 4 - NewID_CurrentLength; i++)
			NewID.insert(NewID.begin(), '0');
	NewID.insert(NewID.begin(), 'P');

	return NewID;
}

void ProductProvider::ReadFile()
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

	// Products
	for (auto i = File["PRODUCTS"].begin(); i != File["PRODUCTS"].end(); ++i)
	{
		Product _Product;
		_Product.ID(i.key());
		_Product.SellerID((*i)["SellerID"]);
		_Product.isR18((*i)["isR18"]);
		_Product.Name((*i)["Name"]);
		_Product.Category((*i)["Category"]);
		_Product.Description((*i)["Description"]);
		_Product.Stock((*i)["Stock"]);
		_Product.Price((*i)["Price"]);
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < (*i)["Rating"][j]; ++k) {
				_Product.Rate(j+1);
			}
		}	
		Products.push_back(_Product);
	}

	// New ID counter
	NewProductIDCounter = File["COUNTERS"]["PRODUCT"];

	f.close();
}

void ProductProvider::WriteFile()
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
		vector<int16_t> Rating = i->RatingArray();
		for (int r = 0; r < 5; r++)
		{
			File["PRODUCTS"][i->ID()]["Rating"][r] = Rating[r];
		}
	}

	// Re-write relevant keys
	File["COUNTERS"]["PRODUCT"] = NewProductIDCounter;

	// Re-write the file
	f.close();
	f.open(DATABASE_PATH, fstream::out | fstream::trunc);
	f << File;

	f.close();
}

bool ProductProvider::isR18(Product _Product)
{
	return _Product.isR18();
}

bool ProductProvider::isRelated(string _SellerID, string _ProductID)
{
	list<Product> FilteredProducts = ProductProvider::GetInstance().ListBySellerID(_SellerID, true);
	bool MatchFound = false;
	for (auto i = FilteredProducts.begin(); i != FilteredProducts.end(); ++i)
	{
		if (i->ID() == _ProductID)
		{
			MatchFound = true;
			break;
		}
	}
	return MatchFound;
}

void ProductProvider::Add(Product _Product)
{
	_Product.ID(ProductProvider::GenerateNewProductID());
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

list<Product> ProductProvider::ListByQuery(string _Query, bool _isR18)
{
	list<Product> _Products;
	for (auto i = Products.begin(); i != Products.end(); ++i)
	{
		if
			(
				   (ToLower(i->Name()).find(ToLower(_Query)) != string::npos)
				|| (ToLower(i->Category()).find(ToLower(_Query)) != string::npos)
			)
		{
			_Products.push_back((*i));
		}
	}

	// Filter R-18 products
	if (!_isR18) _Products.remove_if(ProductProvider::isR18);

	return _Products;
}

list<Product> ProductProvider::ListBySellerID(string _SellerID, bool _isR18)
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
