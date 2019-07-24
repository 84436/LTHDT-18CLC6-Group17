#pragma once
#include "../_INCLUDES_.h"
#include "../Login/LoginProvider.h"
#include "Account.h"
#include "Buyer.h"
#include "Seller.h"
#include "Shipper.h"

class AccountProvider
{
	private:
		AccountProvider();
		~AccountProvider() {}
	public:
		static AccountProvider& GetInstance();

	private:
		list<Account*> Accounts;
		static int32_t NewBuyerIDCounter;
		static int32_t NewSellerIDCounter;
		static int32_t NewShipperIDCounter;
		string GenerateNewAccountID(char AccountType);

	public:
		void ReadFile();
		void WriteFile();

		void Add(Account* _Account, char AccountType);
		void Delete(string _ID);
		Seller* GetSeller(string ID);
		Buyer* GetBuyer(string ID);
		Shipper* GetShipper(string ID);

		list<Shipper*> ListShippers();
};
