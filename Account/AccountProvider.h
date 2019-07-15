#pragma once
#include "../_INCLUDES_.h"

// Hàm băm SHA-256
// được cung cấp bởi http://www.zedwood.com/article/cpp-sha256-function
// CC-BY-SA 3.0

class Account
{
	private:
		string ID;
		string Password;

	public:
		bool Authenticate(string ID, string Password);
};

// thứ giống Login nhưng là Account/People Provider
