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
		~AccountProvider() {}
	public:
		static AccountProvider& GetInstance();

	private:
		list<Account*> Accounts;
		list<PasswordHash> PasswordHashes;
		static int32_t NewBuyerIDCounter;
		static int32_t NewSellerIDCounter;
		static int32_t NewShipperIDCounter;
		string GenerateNewAccountID(char AccountType);

	public:
		void ReadFile();
		void WriteFile();

		string GetPassword();
		bool Login(string _ID, string _HashedPassword);
		void ChangePassword(string _ID, string _HashedPassword);

		void Add(Account* _Account, char AccountType);
		void Delete(string _ID);
		Seller* FindSeller(string ID);
		Buyer* FindBuyer(string ID);
		Shipper* FindShipper(string ID);
};
