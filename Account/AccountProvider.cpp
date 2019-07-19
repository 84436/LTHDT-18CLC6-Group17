#include "AccountProvider.h"

AccountProvider::AccountProvider()
{
	ReadFile();
}

AccountProvider& AccountProvider::GetInstance()
{
	static AccountProvider Instance;
	return Instance;
}

string AccountProvider::GenerateNewAccountID(char AccountType)
{
	string NewID;
	switch (AccountType)
	{
		case 'B':
			NewID = to_string(NewBuyerIDCounter);
			NewBuyerIDCounter++;
			break;
		case 'S':
			NewID = to_string(NewSellerIDCounter);
			NewSellerIDCounter++;
			break;
		case 'H':
			NewID = to_string(NewShipperIDCounter);
			NewShipperIDCounter++;
			break;
		default:
			return "";
	}

	if (NewID.length() < 8)
		for (size_t i = 0; i < 8 - NewID.length(); i++)
			NewID.insert(NewID.begin(), '0');
	NewID.insert(NewID.begin(), AccountType);

	return NewID;
}

void AccountProvider::ReadFile()
{
	fstream f(DATABASE_PATH, fstream::in);
	if (
		!f.is_open()
		|| f.peek() == fstream::traits_type::eof()
		) {
		return;
	}
	json File = json::parse(f);

	// Accounts
	for (auto i = File["ACCOUNTS"].begin(); i != File["ACCOUNTS"].end(); ++i)
	{
		Account* a;

		if (i.key()[0] == 'B') { a = new Buyer; }
		else if (i.key()[0] == 'S') { a = new Seller; }
		else { a = new Shipper; }

		a->ID(i.key());
		a->Name((*i)["Name"]);
		a->Balance((*i)["WalletBalance"]);
		a->YOB((*i)["YearOfBirth"]);
		a->Address((*i)["Address"]);
		a->Email((*i)["Email"]);
		a->Phone((*i)["Phone"]);

		if (i.key()[0] == 'S')
		{
			Seller* b = (Seller*)a;
			b->RatingArray((*i)["Rating"][0], (*i)["Rating"][1], (*i)["Rating"][2], (*i)["Rating"][3], (*i)["Rating"][4]);
		}

		Accounts.push_back(a);
	}

	// Password hashes
	for (auto i = File["HASHES"].begin(); i != File["HASHES"].end(); ++i)
	{
		PasswordHash x = { i.key(), i.value() };
		PasswordHashes.push_back(x);
	}

	// New ID counters
	for (auto i = File["COUNTERS"].begin(); i != File["COUNTERS"].end(); ++i)
	{
		if (i.key() == "BUYER") { NewBuyerIDCounter = i.value(); continue; }
		if (i.key() == "SELLER") { NewSellerIDCounter = i.value(); continue; }
		if (i.key() == "SHIPPER") { NewShipperIDCounter = i.value(); continue; }
	}
}

void AccountProvider::WriteFile()
{
	fstream f(DATABASE_PATH, fstream::in);
	if (
		!f.is_open()
		|| f.peek() == fstream::traits_type::eof()
		) {
		return;
	}
	json File = json::parse(f);

	File["ACCOUNTS"].clear();
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i)
	{
		if ((*i)->ID()[0] == 'S')
		{
			// Sellers: personal info
			File["ACCOUNTS"].push_back(json::object_t::value_type(
				{
					(*i)->ID(),
					{
						{"Name", (*i)->Name()},
						{"Balance", (*i)->Balance()},
						{"YOB", (*i)->YOB()},
						{"Address", (*i)->Address()},
						{"Email", (*i)->Email()},
						{"Phone", (*i)->Phone()},
						{"Rating", {0, 0, 0, 0, 0}}
					}
				}
			));

			// Sellers: get rating count
			Seller* temp = (Seller*)(*i);
			vector<int16_t> Rating = temp->RatingArray();
			for (int r = 0; r < 5; r++)
			{
				File["ACCOUNTS"][(*i)->ID()]["Rating"][r] = Rating[r];
			}
		}
		else
		{
			// everyone else
			File["ACCOUNTS"].push_back(json::object_t::value_type(
				{
					(*i)->ID(),
					{
						{"Name", (*i)->Name()},
						{"Balance", (*i)->Balance()},
						{"YOB", (*i)->YOB()},
						{"Address", (*i)->Address()},
						{"Email", (*i)->Email()},
						{"Phone", (*i)->Phone()}
					}
				}
			));
		}
	}

	File["HASHES"].clear();
	for (auto i = PasswordHashes.begin(); i != PasswordHashes.end(); ++i)
	{
		File["HASHES"].push_back(json::object_t::value_type(
			{ i->ID, i->Hash }
		));
	}

	f << File;
}

char MaskingChar()
{
	string Random = "!@#$%^&*";
	return Random[rand() % Random.length()];
}

void AccountProvider::Add(Account* _Account)
{
	Account* x = nullptr;
	switch (_Account->ID()[0])
	{
		case 'B':
			x = new Buyer(*((Buyer*)_Account));
			break;
		case 'S':
			x = new Seller(*((Seller*)_Account));
			break;
		case 'H':
			x = new Shipper(*((Shipper*)_Account));
			break;
		default:
			return;
	}
	Accounts.push_back(x);
}

string AccountProvider::GetPassword()
{
	srand(time(NULL));

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
	cout << endl << "Plain: " << _HASHED << endl;
	_HASHED = sha256(_HASHED);
	return _HASHED;
}

bool AccountProvider::Login(string _ID, string _HashedPassword)
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

void AccountProvider::ChangePassword(string _ID)
{
	for (auto i = PasswordHashes.begin(); i != PasswordHashes.end(); ++i)
	{
		if (ToLower(i->ID) == ToLower(_ID))
		{
			cout << "Enter password: ";
			string Password1 = GetPassword();
			cout << "Re-enter password: ";
			string Password2 = GetPassword();
			if (Password1 == Password2)
			{
				i->Hash = Password1;
				WriteFile();
				cout << "Password changed." << endl;
			}
			else
			{
				cout << "Passwords do not match. Password changing request aborted." << endl;
			}
		}
	}
	cout << "Account not found." << endl;
}

void AccountProvider::Delete(string _ID)
{
	// Remove related products

	// Mark pending order + add note

	// Actually delete account
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i)
	{
		if (ToLower((**i).ID()) == ToLower(_ID)) {
			Accounts.erase(i);
			break;
		}
	}
}

Seller* AccountProvider::FindSeller(string ID) {
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i) {
		if ((*i)->ID() == ID)
			return (Seller*)(*i);
	}
	return nullptr;
}

Buyer* AccountProvider::FindBuyer(string ID) {
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i) {
		if ((*i)->ID() == ID)
			return (Buyer*)(*i);
	}
	return nullptr;
}

Shipper* AccountProvider::FindShipper(string ID) {
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i) {
		if ((*i)->ID() == ID)
			return (Shipper*)(*i);
	}
	return nullptr;
}
