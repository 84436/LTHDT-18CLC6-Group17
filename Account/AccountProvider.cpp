#include "AccountProvider.h"

int32_t AccountProvider::NewBuyerIDCounter = 0;
int32_t AccountProvider::NewSellerIDCounter = 0;
int32_t AccountProvider::NewShipperIDCounter = 0;

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

	size_t NewID_CurrentLength = NewID.length();

	if (NewID_CurrentLength < 4)
		for (size_t i = 0; i < 4 - NewID_CurrentLength; i++)
			NewID.insert(NewID.begin(), '0');
	NewID.insert(NewID.begin(), AccountType);

	return NewID;
}

void AccountProvider::ReadFile()
{
	fstream f;
	f.open(DATABASE_PATH, fstream::in);
	if (!f.is_open() || f.peek() == fstream::traits_type::eof())
	{
		cout << "Database either is inaccessible or does not exist." << endl;
		exit(-1);
	}
	json File = json::parse(f);

	// Accounts
	for (auto i = File["ACCOUNTS"].begin(); i != File["ACCOUNTS"].end(); ++i)
	{
		Account* a = nullptr;

		switch (i.key()[0])
		{
			case 'B': a = new Buyer; break;
			case 'S': a = new Seller; break;
			case 'H': a = new Shipper; break;
		}

		a->ID(i.key());
		a->Name((*i)["Name"]);
		a->Balance((*i)["Balance"]);
		a->YOB((*i)["YOB"]);
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

	// New ID counters
	for (auto i = File["COUNTERS"].begin(); i != File["COUNTERS"].end(); ++i)
	{
		if (i.key() == "BUYER") { NewBuyerIDCounter = i.value(); continue; }
		if (i.key() == "SELLER") { NewSellerIDCounter = i.value(); continue; }
		if (i.key() == "SHIPPER") { NewShipperIDCounter = i.value(); continue; }
	}

	f.close();
}

void AccountProvider::WriteFile()
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

	// Re-write the relevant object
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

	// Re-write relevant keys
	File["COUNTERS"]["BUYER"] = NewBuyerIDCounter;
	File["COUNTERS"]["SELLER"] = NewSellerIDCounter;
	File["COUNTERS"]["SHIPPER"] = NewShipperIDCounter;

	// Re-write the file
	f.close();
	f.open(DATABASE_PATH, fstream::out | fstream::trunc);
	f << File;

	f.close();
}

void AccountProvider::Add(Account* _Account, char AccountType)
{
	Account* x = nullptr;
	switch (AccountType)
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
	x->ID(GenerateNewAccountID(AccountType));
	LoginProvider::GetInstance().Add(x->ID(), sha256(""));

	cout << "New account ID = " << x->ID() << endl;
	Accounts.push_back(x);
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

	// Delete password hash
}

Seller* AccountProvider::GetSeller(string ID)
{
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i) {
		if ((*i)->ID() == ID)
			return (Seller*)(*i);
	}
	return nullptr;
}

Buyer* AccountProvider::GetBuyer(string ID)
{
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i) {
		if ((*i)->ID() == ID)
			return (Buyer*)(*i);
	}
	return nullptr;
}

Shipper* AccountProvider::GetShipper(string ID)
{
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i) {
		if ((*i)->ID() == ID)
			return (Shipper*)(*i);
	}
	return nullptr;
}

list<Shipper*> AccountProvider::ListShippers()
{
	list<Shipper*> Shippers;

	for (auto i = Accounts.begin(); i != Accounts.end(); ++i) {
		if ((**i).ID()[0] == 'H')
		{
			Shippers.push_back((Shipper*)(*i));
		}
	}

	return Shippers;
}
