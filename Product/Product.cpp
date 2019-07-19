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

void Product::GetInfo(){
	cout << endl << "PROVIDER : " << _SellerID << endl;
	cout << "PRODUCT INFORMATION : " << endl;
	cout << "ID : " << _ID << endl;
	cout << "R18 : " << _isR18 << endl;
	cout << "Name : " << _Name << endl;
	cout << "Category : " << _Category << endl;
	cout << "Decription : " << _Decription << endl;
	cout << "Stock : " << _Stock << endl;
	cout << "Price : " << _Price << endl;
	//cout << "Rating : " << (1 * Rating[0] + 2 * Rating[1] + 3 * Rating[2] + 4 * Rating[3] + 5 * Rating[4]) / (Rating[0] + Rating[1] + Rating[2] + Rating[3] + Rating[4]) << endl;
}

void Product::Rate(int){
	int n;
	cout << "How many Stars you want to rate this Product (1 - 5) : ";
	cin >> n;
	_Rating[n - 1]++;
}
