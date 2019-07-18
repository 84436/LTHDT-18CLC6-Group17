#include "Account.h"

//string  Account::ID() { return this->_ID; }
//void    Account::ID(string ID) { this->_ID = ID; }
//string  Account::Name() { return this->_Name; }
//void    Account::Name(string Name) { this->_Name = Name; }
//int64_t Account::Balance() { return this->_Balance.checkWallet(); }
//void    Account::Balance(int64_t Balance) { this->_Balance.setBalance(Balance); }
//int64_t Account::YOB() { return this->_YOB; }
//void    Account::YOB(int64_t YOB) { this->_YOB = YOB; }
//string  Account::Address() { return this->_Address; }
//void    Account::Address(string Address) { this->_Address = Address; }
//string  Account::Email() { return this->_Email; }
//void    Account::Email(string Email) { this->_Email = Email; }
//string  Account::Phone() { return this->_Phone; }
//void    Account::Phone(string Phone) { this->_Phone = Phone; }

Account::Account()
{
	_ID = "";
	_Name = "";
	_Balance.setBalance(0);
	_YOB = 0;
	_Address = "";
	_Email = "";
	_Phone = "";
}

Account::Account(const Account& a)
{
	// TODO: my money or your money?
	this->_Balance = a._Balance;
	this->_ID = a._ID;
	this->_Name = a._Name;
	this->_YOB = a._YOB;
	this->_Address = a._Address;
	this->_Email = a._Email;
	this->_Phone = a._Phone;
}

Account::Account(string _ID, string _Name, int64_t _Balance, int64_t _YOB, string _Address , string _Email, string _Phone) {
	ID(_ID);
	Name(_Name);
	Balance(_Balance);
	YOB(_YOB);
	Address(_Address);
	Email(_Email);
	Phone(_Phone);
}

void Account::EditInfo() {
	string a;
	cout << " \t Account Information : \n";
	cout << "ID : \t" << ID() << endl;
	cout << "NAME : \t" << Name() << endl;
	cout << "YEAR of BIRTH :\t" << YOB() << endl;
	cout << "ADDRESS : \t" << Address() << endl;
	cout << "EMAIL : \t" << Email() << endl;
	cout << "PHONE NUMBER : \t" << Phone() << endl;
	cout << endl << endl << "Do you want to change your infomation ? (Y/N) :" << endl;
	while (getchar() != '\n');
	getline(cin, a);

	if (ToLower(a) == ToLower("Y")) {
		cout << " \t Account Information : \n";
		cout << "ID : \t"; getline(cin, _ID);
		cout << "NAME : \t"; getline(cin, _Name);
		cout << "YEAR of BIRTH :\t"; cin >> _YOB;
		cout << "ADDRESS : \t"; while (getchar() != '\n'); getline(cin, _Address);
		cout << "EMAIL : \t"; getline(cin, _Email);
		cout << "PHONE NUMBER : \t"; getline(cin, _Phone);
	}
	return;
}

void Account::OutputInfo(){
	cout << "ID            : " << ID() << endl;
	cout << "Name          : " << Name() << endl;
	cout << "Year of Birth : " << YOB() << endl;
	cout << "Address       : " << Address() << endl;
	cout << "Email         : " << Email() << endl;
	cout << "Phone         : " << Phone() << endl;
}
