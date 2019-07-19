#include "Product.h"

Product::Product(const Product& p)
{
	this->_SellerID = p._SellerID;
	this->_ID = p._ID;
	this->_Name = p._Name;
	this->_Category = p._Category;
	this->_Decription = p._Decription;
	this->_Stock = p._Stock;
	this->_Price = p._Price;

	for (int i = 0; i < 5; i++) {
		this->_Rating[i] = p._Rating[i];
	}
}

void Product::GetInfo()
{
	cout << "Name       : " << _Name << endl;
	cout << "ID         : " << _ID << endl;
	cout << "Seller     : " << AccountProvider::GetInstance().FindSeller(_SellerID)->Name() << " (ID: " << _SellerID << ")" << endl;
	cout << "Is R18?    : " << (_isR18 ? "true" : "false") << endl;
	cout << "Category   : " << _Category << endl;
	cout << "Decription : " << _Decription << endl;
	cout << "Stock      : " << _Stock << endl;
	cout << "Price      : " << _Price << endl;
	cout << "Rate       : " << Rate() << endl;
}

float Product::Rate()
{
	return (1 * _Rating[0] + 2 * _Rating[1] + 3 * _Rating[2] + 4 * _Rating[3] + 5 * _Rating[4]) / (_Rating[0] + _Rating[1] + _Rating[2] + _Rating[3] + _Rating[4]);
}

void Product::Rate(int _Rate)
{
	_Rating[_Rate - 1]++;
}
