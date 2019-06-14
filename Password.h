#pragma once

// Hàm băm SHA-256
// được cung cấp bởi http://www.zedwood.com/article/cpp-sha256-function
// CC-BY-SA 3.0
#include "sha256/sha256.h"

#include <iostream>
#include <string>
using namespace std;

class Password
{
	private:
		string data;

	public:
		void GetPassword(); // lấy và băm pass, đưa vào data
		bool operator== (const Password& x); // so sánh
};

void dosomething();