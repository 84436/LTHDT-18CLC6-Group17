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

Seller* AccountProvider::findSeller(string ID) {
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i) {
		if ((*i)->ID() == ID)
			return (Seller*)(*i);
	}
	return nullptr;
}

Buyer* AccountProvider::findBuyer(string ID) {
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i) {
		if ((*i)->ID() == ID)
			return (Buyer*)(*i);
	}
	return nullptr;
}

Shipper* AccountProvider::findShipper(string ID) {
	for (auto i = Accounts.begin(); i != Accounts.end(); ++i) {
		if ((*i)->ID() == ID)
			return (Shipper*)(*i);
	}
	return nullptr;
}