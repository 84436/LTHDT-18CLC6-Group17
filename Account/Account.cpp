#include "Account.h"
#include "../Order/OrderProvider.h"

Account::Account(const Account& a)
{
	this->_ID = a._ID;
	this->_Name = a._Name;
	this->_YOB = a._YOB;
	this->_Address = a._Address;
	this->_Email = a._Email;
	this->_Phone = a._Phone;
	this->_Wallet.Balance(a._Wallet.Balance());
}

int64_t Account::GetAge()
{
	return 2019 - this->_YOB;
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


void Account::Deposit(int64_t _Balance)
{
	this->_Wallet.Deposit(_Balance);
}

void Account::Withdraw(int64_t _Balance)
{
	this->_Wallet.Withdraw(_Balance);
}

void Account::ListOrder()
{
	list<Order> FilteredOrders = OrderProvider::GetInstance().Search(this->ID());
	if (FilteredOrders.size() == 0)
	{
		cout << "No orders." << endl;
		return;
	}
	for (auto i = FilteredOrders.begin(); i != FilteredOrders.end(); ++i)
	{
		cout << (*i).ID() << ": " << (*i).Status_String() << endl;
	}
}

void Account::GetOrderInfo(string _OrderID)
{
	OrderProvider::GetInstance().GetByID(_OrderID)->GetInfo();
}
