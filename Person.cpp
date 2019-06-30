#include "Person.h"

Person::Person(string id, string name, uint64_t x, uint64_t yob, string address , string email, string phone) {
	Money.Deposit(x);
	ID = id;
	Name = name;
	YOB = yob;
	Address = address;
	Email = email;
	Phone = phone;
}

Person::Person(string id, string name, uint64_t yob, string address, string email, string phone) {
	ID = id;
	Name = name;
	YOB = yob;
	Address = address;
	Email = email;
	Phone = phone;
}

void Person::EditInfo() {
	string a;
	cout << " \t Account Information : \n";
	cout << "ID : \t" << ID << endl;
	cout << "NAME : \t" << Name << endl;
	cout << "YEAR of BIRTH :\t" << YOB << endl;
	cout << "ADDRESS : \t" << Address << endl;
	cout << "EMAIL : \t" << Email << endl;
	cout << "PHONE NUMBER : \t" << Phone << endl;
	cout << endl << endl << "Do you want to change your infomation ? (Y/N) :" << endl;
	while (getchar() != '\n');
	getline(cin, a);
	if (a == "Y") {
		cout << " \t Account Information : \n";
		cout << "ID : \t"; getline(cin, ID); cout << endl;
		cout << "NAME : \t"; getline(cin, Name); cout << endl;
		cout << "YEAR of BIRTH :\t"; cin >> YOB; cout << endl;
		cout << "ADDRESS : \t"; while (getchar() != '\n'); getline(cin, Address); cout << endl;
		cout << "EMAIL : \t"; getline(cin, Email); cout << endl;
		cout << "PHONE NUMBER : \t"; getline(cin, Phone); cout << endl;
	}
	return;
}