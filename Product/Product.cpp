#include "Product.h"

Product::Product(const Product& _Product)
{
	this->_SellerID = _Product._SellerID;
	this->_ID = _Product._ID;
	this->_isR18 = _Product._isR18;
	this->_Name = _Product._Name;
	this->_Category = _Product._Category;
	this->_Description = _Product._Description;
	this->_Stock = _Product._Stock;
	this->_Price = _Product._Price;

	for (int i = 0; i < 5; i++) {
		this->_Rating[i] = _Product._Rating[i];
	}
}

void Product::GetInfo()
{
	cout << "Name       : " << _Name << endl;
	cout << "ID         : " << _ID << endl;
	cout << "Seller     : " << (AccountProvider::GetInstance().GetSeller(this->SellerID()) == nullptr ? "n/a" : this->SellerID() + " (" + AccountProvider::GetInstance().GetSeller(this->SellerID())->Name() + ")") << endl;
	cout << "Is R18?    : " << (_isR18 ? "true" : "false") << endl;
	cout << "Category   : " << _Category << endl;
	cout << "Decription : " << _Description << endl;
	cout << "Stock      : " << _Stock << endl;
	cout << "Price      : " << _Price << endl;
	cout << "Rate       : " << Rate() << endl;
}

void Product::EditInfo()
{
	string s;
	cout << "Name [" << this->Name() << "] : "; getline(cin, s); if (!isEmptyString(s)) this->Name(s); s.clear();
	cout << "Is R18? [" << (this->isR18() ? "true" : "false") << "] : "; getline(cin, s); if (!isEmptyString(s)) this->isR18(s == "true" ? true : false); s.clear();
	cout << "Category [" << this->Category() << "] : "; getline(cin, s); if (!isEmptyString(s)) this->Category(s); s.clear();
	cout << "Description [" << this->Description() << "] : "; getline(cin, s); if (!isEmptyString(s)) this->Description(s); s.clear();
	cout << "Price [" << this->Price() << "] : "; getline(cin, s); if (!isEmptyString(s)) this->Price(stoi(s)); s.clear();
}

vector<int16_t> Product::RatingArray()
{
	return _Rating;
}

void Product::RatingArray(int16_t _1, int16_t _2, int16_t _3, int16_t _4, int16_t _5)
{
	this->_Rating[0] = _1;
	this->_Rating[1] = _2;
	this->_Rating[2] = _3;
	this->_Rating[3] = _4;
	this->_Rating[4] = _5;
}

float Product::Rate()
{
	// No rating
	if (_Rating[0] + _Rating[1] + _Rating[2] + _Rating[3] + _Rating[4] == 0) return 0;
	// Normal case
	return (float)(1 * _Rating[0] + 2 * _Rating[1] + 3 * _Rating[2] + 4 * _Rating[3] + 5 * _Rating[4]) / (float)(_Rating[0] + _Rating[1] + _Rating[2] + _Rating[3] + _Rating[4]);
}

void Product::Rate(int _Rate)
{
	_Rating[_Rate - 1]++;
}

void Product::AddStock(int32_t amount)
{
	this->_Stock += amount;
}
