#pragma once

// C++ STL
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
using namespace std;

// SHA256, password hashing
#include "sha256/sha256.h"

// JSON, database
#include "json/json.hpp"
using json = nlohmann::json;

// Internals
#include "Account/Account.h"
#include "Account/AccountProvider.h"
#include "Account/Buyer.h"
#include "Account/Seller.h"
#include "Account/Shipper.h"
#include "Account/Wallet.h"
#include "Database/Database.h"
#include "Product/Product.h"
#include "Product//ProductProvider.h"
#include "Order/Order.h"
#include "Order/OrderProvider.h"

// Constants
auto constexpr DATABASE_PATH = "C:/db.json";

// Inline string helpers
inline bool isEmptyString(const string& s)
{
	return (s.empty() || s.find_first_not_of(' ') != string::npos);
}
inline string ToLower(const string& s)
{
	string Lowered;
	for (auto i = s.begin(); i != s.end(); ++i)
	{
		Lowered.push_back(tolower(*i));
	}
	return Lowered;
}
