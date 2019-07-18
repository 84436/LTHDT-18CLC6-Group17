#include "Account.h"

Account::Account(ProductProvider* _ProductProvider, OrderProvider* _OrderProvider)
{
	this->_ProductProvider = _ProductProvider;
	this->_OrderProvider = _OrderProvider;
}

Account::Account(const Account& a)
{
	this->_ProductProvider = a._ProductProvider;
	this->_OrderProvider = a._OrderProvider;
	this->_ID = a._ID;
	this->_Name = a._Name;
	this->_YOB = a._YOB;
	this->_Address = a._Address;
	this->_Email = a._Email;
	this->_Phone = a._Phone;
	this->_Wallet.Balance(a._Wallet.Balance());
}

void Account::EditInfo()
{
	string s;
	cout << "Name [" << this->Name() << "] : "; getline(cin, s); if (!isEmptyString(s)) this->Name(s); s.clear();
	cout << "Year of Birth [" << this->YOB() << "] : "; getline(cin, s); if (!isEmptyString(s)) this->YOB(stoi(s)); s.clear();
	cout << "Address [" << this->Address() << "] : "; getline(cin, s); if (!isEmptyString(s)) this->Address(s); s.clear();
	cout << "Email [" << this->Email() << "] : "; getline(cin, s); if (!isEmptyString(s)) this->Email(s); s.clear();
	cout << "Phone [" << this->Phone() << "] : "; getline(cin, s); if (!isEmptyString(s)) this->Phone(s); s.clear();
}

void Account::OutputInfo(){
	cout << "ID            : " << ID() << endl;
	cout << "Name          : " << Name() << endl;
	cout << "Year of Birth : " << YOB() << endl;
	cout << "Address       : " << Address() << endl;
	cout << "Email         : " << Email() << endl;
	cout << "Phone         : " << Phone() << endl;
}
