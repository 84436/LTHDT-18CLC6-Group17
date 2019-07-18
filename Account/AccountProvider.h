#pragma once
#include "../_INCLUDES_.h"

struct PasswordHash
{
	string ID;
	string Hash;
};

class AccountProvider : public Provider
{
	private:
		list<Account*> Accounts;
		list <PasswordHash> PasswordHashes;

	public:
		void ReadFile();
		void WriteFile();
		bool Authenticate(string ID, string Password);
		Seller* FindSeller(string ID);
		Buyer* FindBuyer(string ID);
		Shipper* FindShipper(string ID);
};

// thứ giống Login nhưng là Account/People Provider