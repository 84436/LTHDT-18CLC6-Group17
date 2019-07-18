#pragma once
#include "../_INCLUDES_.h"
#include "Wallet.h"

class Account {
	protected:
		string _ID;
		string _Name;
		Wallet _Balance;
		int64_t _YOB;
		string _Address;
		string _Email;
		string _Phone;

	public:
		Account();
		Account(string _ID, string _Name, int64_t _Balance, int64_t _YOB, string _Address, string _Email, string _Phone);
		Account(const Account& a);

		// Getters + Setters.
		string  ID()					 { return this->_ID; }
		void    ID(string ID)			 { this->_ID = ID; }
		string  Name()					 { return this->_Name; }
		void    Name(string Name)		 { this->_Name = Name; }
		int64_t Balance()				 { return this->_Balance.checkWallet(); }
		void    Balance(int64_t Balance) { this->_Balance.setBalance(Balance); }
		int64_t YOB()					 { return this->_YOB; }
		void    YOB(int64_t YOB)		 { this->_YOB = YOB; }
		string  Address()				 { return this->_Address; }
		void    Address(string Address)  { this->_Address = Address; }
		string  Email()					 { return this->_Email; }
		void    Email(string Email)		 { this->_Email = Email; }
		string  Phone()					 { return this->_Phone; }
		void    Phone(string Phone)		 { this->_Phone = Phone; }

		//string  ID();
		//void    ID(string ID);
		//string  Name();
		//void    Name(string Name);
		//int64_t Balance();
		//void    Balance(int64_t Balance);
		//int64_t YOB();
		//void    YOB(int64_t YOB);
		//string  Address();
		//void    Address(string Address);
		//string  Email();
		//void    Email(string Email);
		//string  Phone();
		//void    Phone(string Phone);

		void EditInfo();
		// void ChangePassword(Login& h);
		void OutputInfo();
};
