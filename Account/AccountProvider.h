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
		static int64_t NewAccountIDCounter;
		string GenerateNewAccountID();

	public:
		void ReadFile();
		void WriteFile();

		string GetPassword();
		bool Login(string _ID, string _HashedPassword);
		void ChangePassword(string _ID);

		void Add(Account* _Account);
		void Delete(string _ID);
		Seller* FindSeller(string ID);
		Buyer* FindBuyer(string ID);
		Shipper* FindShipper(string ID);
};
