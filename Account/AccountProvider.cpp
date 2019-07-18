#include "AccountProvider.h"

//void Account::GetPassword()
//{
//	// mask field
//	
//	char c = 0;
//	while (c = cin.get()) {
//		if (c == 8) { // BACKSPACE
//
//		}
//		else if (c == 13) { // RETURN
//
//		}
//		else if (c == 0 || c == 224) { // CONTROL CHARS
//
//		}
//		else {
//
//		}
//	}
//
//	// băm
//}
//
//bool Account::operator==(const Password& x)
//{
//	return (data == x.data);
//}
//
//bool Account::Authenticate(string ID, string Password)
//{
//	return (sha256(ID) == this->ID && sha256(Password) == this->Password);
//}
//
//Login::Login()
//{
//}
//
//Login::Login(const Login& x)
//{
//	for (auto i = x.Accounts.begin(); i != x.Accounts.end(); i++) {
//		this->Accounts.push_back((*i));
//	}
//}
//
//Login::~Login()
//{
//	Accounts.clear();
//}

AccountProvider::AccountProvider()
{
	ReadFile();
}

AccountProvider& AccountProvider::GetInstance()
{
	static AccountProvider Instance;
	return Instance;
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
			vector<uint16_t> Rating = temp->RatingArray();
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

	/*File["HASHES"].clear();
	for (auto i = PasswordHashes.begin(); i != PasswordHashes.end(); ++i)
	{
		File["HASHES"].push_back(json::object_t::value_type(
			{ i->ID, i->Hash }
		));
	}*/

	f << File;
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
