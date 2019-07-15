#pragma once
#include "../_INCLUDES_.h"

class Account {
	protected:
		string ID;
		string Name;
		Wallet Money;
		int64_t YOB;
		string Address;
		string Email;
		string Phone;
		vector<Order*> FillteredOrder;

	public:
		Account();
		Account(const Account& p);
		Account(string ID, string Name, int64_t Balance, int64_t YOB, string Address, string Email, string Phone);
		Account(string, string, int64_t, string, string, string);
		~Account();

		void EditInfo();
		// void ChangePassword(Login& h);
		void DeleteAccount();
		void OutputInfo();
};
