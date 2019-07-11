#pragma once
#include "_INCLUDES_.h"

class Person {
	protected:
		string ID;
		string Name;
		Wallet Money;
		uint64_t YOB;
		string Address;
		string Email;
		string Phone;
		vector<Order*> FillteredOrder;

	public:
		Person();
		Person(const Person& p);
		Person(string ID, string Name, uint64_t Balance, uint64_t YOB, string Address, string Email, string Phone);
		Person(string, string, uint64_t, string, string, string);
		~Person();

		void EditInfo();
		void ChangePassword(Login& h);
		void DeleteAccount();
		void OutputInfo();
};
