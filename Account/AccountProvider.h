#pragma once
#include "../_INCLUDES_.h"
#include "Account.h"
#include "Buyer.h"
#include "Seller.h"
#include "Shipper.h"

struct PasswordHash
{
	string ID;
	string Hash;
};

class AccountProvider
{
	private:
		AccountProvider();
	public:
		static AccountProvider& GetInstance();

	private:
		list<Account*> Accounts;
		list<PasswordHash> PasswordHashes;

	public:
		void ReadFile();
		void WriteFile();
		// bool Authenticate(string ID, string Password);
		void Delete(string _ID);
		Seller* FindSeller(string ID);
		Buyer* FindBuyer(string ID);
		Shipper* FindShipper(string ID);
};

// thứ giống Login nhưng là Account/People Provider