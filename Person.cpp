#include "Person.h"
#include "Shipper.h"

Person::Person()
{
	ID = "";
	Name = "";
	Money.setBalance(0);
	YOB = 0;
	Address = "";
	Email = "";
	Phone = "";
}

Person::Person(const Person& p)
{
	// TODO: my money or your money?
	this->Money = p.Money;
	this->ID = p.ID;
	this->Name = p.Name;
	this->YOB = p.YOB;
	this->Address = p.Address;
	this->Email = p.Email;
	this->Phone = p.Phone;
}

Person::Person(string ID, string Name, uint64_t Balance, uint64_t YOB, string Address , string Email, string Phone) {
	Money.Deposit(Balance);
	this->ID = ID;
	this->Name = Name;
	this->YOB = YOB;
	this->Address = Address;
	this->Email = Email;
	this->Phone = Phone;
}

Person::Person(string id, string name, uint64_t yob, string address, string email, string phone) {
	ID = id;
	Name = name;
	YOB = yob;
	Address = address;
	Email = email;
	Phone = phone;
}

Person::~Person()
{
	this->FillteredOrder.clear();
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

void Person::DeleteAccount()
{
	this->~Person();
}

void Person::OutputInfo(){
	cout << "ID            : " << ID << endl;
	cout << "Name          : " << Name << endl;
	cout << "Year of Birth : " << YOB << endl;
	cout << "Address       : " << Address << endl;
	cout << "Email         : " << Email << endl;
	cout << "Phone         : " << Phone << endl;
}
