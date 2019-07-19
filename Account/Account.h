#pragma once
#include "../_INCLUDES_.h"
#include "Wallet.h"

class Account {
	protected:
		string _ID;
		string _Name;
		int64_t _YOB = 1;
		string _Address;
		string _Email;
		string _Phone;
		Wallet _Wallet;

	public:
		Account() {}
		Account(const Account& a);

		string  ID			()					{ return this->_ID; }
		void    ID			(string _ID)		{ this->_ID = _ID; }
		string  Name		()					{ return this->_Name; }
		void    Name		(string _Name)		{ this->_Name = _Name; }
		int64_t YOB			()					{ return this->_YOB; }
		void    YOB			(int64_t _YOB)		{ this->_YOB = _YOB; }
		string  Address		()					{ return this->_Address; }
		void    Address		(string _Address)	{ this->_Address = _Address; }
		string  Email		()					{ return this->_Email; }
		void    Email		(string _Email)		{ this->_Email = _Email; }
		string  Phone		()					{ return this->_Phone; }
		void    Phone		(string _Phone)		{ this->_Phone = _Phone; }
		int64_t Balance		()					{ return this->_Wallet.Balance(); }
		void    Balance		(int64_t _Balance)	{ this->_Wallet.Balance(_Balance); }

		void Deposit(int64_t _Balance);
		void Withdraw(int64_t _Balance);

		int64_t GetAge();
		void EditInfo();
		virtual void OutputInfo();

		void ListOrder();
		void GetOrderInfo(string _OrderID);
};
