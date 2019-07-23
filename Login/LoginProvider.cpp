#include "LoginProvider.h"

LoginProvider::LoginProvider()
{
	ReadFile();
}

LoginProvider& LoginProvider::GetInstance()
{
	static LoginProvider Instance;
	return Instance;
}

void LoginProvider::ReadFile()
{
	fstream f;
	f.open(DATABASE_PATH, fstream::in);
	if (
		!f.is_open()
		|| f.peek() == fstream::traits_type::eof()
		)
	{
		cout << "Database does not exist." << endl;
		return;
	}
	json File = json::parse(f);

	// Password hashes
	for (auto i = File["HASHES"].begin(); i != File["HASHES"].end(); ++i)
	{
		PasswordHash x = { i.key(), i.value() };
		PasswordHashes.push_back(x);
	}

	f.close();
}

void LoginProvider::WriteFile()
{
	// Parse existing file
	fstream f;
	f.open(DATABASE_PATH, fstream::in);
	if (
		!f.is_open()
		|| f.peek() == fstream::traits_type::eof()
		)
	{
		cout << "Database does not exist." << endl;
		return;
	}
	json File = json::parse(f);

	// Re-write password-hashes
	File["HASHES"].clear();
	for (auto i = PasswordHashes.begin(); i != PasswordHashes.end(); ++i)
	{
		File["HASHES"].push_back(json::object_t::value_type(
			{ i->ID, i->Hash }
		));
	}

	// Re-write the file
	f.close();
	f.open(DATABASE_PATH, fstream::out | fstream::trunc);
	f << File;

	f.close();
}

void LoginProvider::Add(string _ID, string _HashedPassword)
{
	PasswordHashes.push_back({ _ID, _HashedPassword });
}

void LoginProvider::Delete(string _ID)
{
	for (auto i = PasswordHashes.begin(); i != PasswordHashes.end(); ++i)
	{
		if (i->ID == _ID)
		{
			PasswordHashes.erase(i);
			return;
		}
	}
}

char LoginProvider::MaskingChar()
{
	string Random = "!@#$%^&*";
	return Random[rand() % Random.length()];
}

string LoginProvider::GetPassword()
{
	srand((unsigned int)time(nullptr));

	string _HASHED;
	char c = 0;
	while (c = _getch())
	{
		if (c == 8) // BKSP
		{
			if (_HASHED.size() == 0)
				continue;
			else if (_HASHED.size() == 1)
			{
				_HASHED.pop_back();
				cout << "\b \b";
			}
			else
			{
				_HASHED.pop_back();
				cout << "\b \b\b" << MaskingChar() << " \b";
			}
		}
		else if (c == 13) // RETURN
		{
			if (_HASHED.size() > 0) cout << "\b \b";
			break;
		}
		else if (c == 0 || c == 224) // CTRL
		{
			_getch();
		}
		else
		{
			_HASHED.push_back(c);
			if (_HASHED.size() - 1 == 0) cout << MaskingChar();
			else cout << "\b " << MaskingChar();
		}
	}
	cout << endl;

	_HASHED = sha256(_HASHED);
	return _HASHED;
}

bool LoginProvider::Login(string _ID, string _HashedPassword)
{
	for (auto i = PasswordHashes.begin(); i != PasswordHashes.end(); ++i)
	{
		if (ToLower(i->ID) == ToLower(_ID))
		{
			return (i->Hash == _HashedPassword);
		}
	}
	return false;
}

void LoginProvider::ChangePassword(string _ID, string _HashedPassword)
{
	for (auto i = PasswordHashes.begin(); i != PasswordHashes.end(); ++i)
	{
		if (ToLower(i->ID) == ToLower(_ID))
		{
			i->Hash = _HashedPassword;
			WriteFile();
			return;
		}
	}
}
