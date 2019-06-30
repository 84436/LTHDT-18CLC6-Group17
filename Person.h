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
	Person(string,string,uint64_t);
	Person(string, string);
	void EditInfo();
	void ChangePassWord();
	void DeleteAccount();
};