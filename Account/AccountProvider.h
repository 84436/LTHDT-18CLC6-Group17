#pragma once
#include "../_INCLUDES_.h"

// Hàm băm SHA-256
// được cung cấp bởi http://www.zedwood.com/article/cpp-sha256-function
// CC-BY-SA 3.0

class AccountProvider
{
	private:
		string ID;
		string Password;
		list<Account*> Accounts;

	public:
		bool Authenticate(string ID, string Password);

		Seller* findSeller(string ID);
		Buyer* findBuyer(string ID);
		Shipper* findShipper(string ID);
};

// thứ giống Login nhưng là Account/People Provider