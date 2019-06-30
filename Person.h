#include "Wallet.h"

class Person {
protected:
	string ID;
	string Name;
	Wallet Money;
	uint64_t YOB;
	string Address;
	string Email;
	string Phone;
public:
	Person(string id, string name, uint64_t x);
	Person(string id, string name);
	void EditInfo();
	void ChangePassWord();
	void DeleteAccount();
};