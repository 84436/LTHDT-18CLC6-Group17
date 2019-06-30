#include "Person.h"

Person::Person(string id, string name, uint64_t x) {
	Money.Deposit(x);
	ID = id;
	Name = name;
}

Person::Person(string id, string name) {
	ID = id;
	Name = name;
}

void Person::EditInfo() {
	cout << " \t Account Information : \n";
	cout << "ID : \t" << ID << endl;
	cout << "NAME : \t" << Name << endl;
	
}