#pragma once
#include "../_INCLUDES_.h"
#include "../Account/AccountProvider.h"

struct PasswordHash
{
	string ID;
	string Hash;
};

class LoginProvider
{
	private:
		LoginProvider();
		~LoginProvider() {}
	public:
		static LoginProvider& GetInstance();

	private:
		list<PasswordHash> PasswordHashes;
	public:
		void ReadFile();
		void WriteFile();

		void Add(string _ID, string _HashedPassword);
		void Delete(string _ID);

		static char MaskingChar();
		string GetPassword();
		bool Login(string _ID, string _HashedPassword);
		void ChangePassword(string _ID, string _HashedPassword);
};
