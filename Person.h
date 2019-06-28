#include "Wallet.h"

class Person {
protected:
	string ID;
	string Name;
	Wallet Money;
public:
	Person(string,string,uint64_t);
	Person(string, string);

};