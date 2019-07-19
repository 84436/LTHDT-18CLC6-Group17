#pragma once

// C++ STL
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <ctime> // password
#include <conio.h> // password
using namespace std;

// SHA256, password hashing
// http://www.zedwood.com/article/cpp-sha256-function
// CC-BY-SA 3.0
#include "sha256/sha256.h"

// JSON, database
#include "json/json.hpp"
using json = nlohmann::json;

// Forward declarations, because classes.
class Account;
class Buyer;
class Seller;
class Shipper;
class Product;
class Order;
class AccountProvider;
class ProductProvider;
class OrderProvider;

// Constants
auto constexpr DATABASE_PATH = "D:/db.json";

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

// Get current day, month, year
