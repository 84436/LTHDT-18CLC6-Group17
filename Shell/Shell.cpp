#include "Shell.h"
#include "../Login/LoginProvider.h"
#include "../Order/OrderProvider.h"

Shell& Shell::GetInstance()
{
	static Shell Instance;
	return Instance;
}

Shell::Shell()
{
	AccountProvider::GetInstance();
	ProductProvider::GetInstance();
	OrderProvider::GetInstance();
}

Shell::~Shell()
{
	AccountProvider::GetInstance().WriteFile();
	ProductProvider::GetInstance().WriteFile();
	OrderProvider::GetInstance().WriteFile();
	exit(0);
}

void Shell::Loop()
{

	// Login
	while (true)
	{
		LogIn();

		// Login successfully
		if (!_AccountID.empty())
		{
			Greeter();
			while (true) {
				string _Command;
				cout << "(" << _AccountID << ")> ";
				getline(cin, _Command);
				
				// Clear screen
				if (ToLower(_Command) == "cls")
				{
					system("CLS");
					continue;
				}

				// Logout
				if (ToLower(_Command) == "logout")
				{
					_AccountID.clear();
					system("CLS");
					break;
				}

				// Interpret commands
				Interpret(_Command);

				cout << endl;
			}
		}
	}
}

void Shell::LogIn()
{
	cout << "ID       : ";
	string _CurrentAccountID;
	getline(cin, _CurrentAccountID);

	if (_CurrentAccountID == "new")
	{
		NewAccount();
		system("PAUSE");
		system("CLS");
		return;
	}

	if (_CurrentAccountID == "exit")
	{
		this->~Shell();
	}

	cout << "Password : ";
	string _CurrentPassword = LoginProvider::GetInstance().GetPassword();

	if (LoginProvider::GetInstance().Login(_CurrentAccountID, _CurrentPassword))
	{
		this->_AccountID = _CurrentAccountID;
		system("CLS");
	}
	else
	{
		cout << "Incorrect credentials. Try again." << endl << endl;
	}
}

void Shell::NewAccount()
{
	string type;

	do
	{
		cout << "Type of account? [1=Buyer, 2=Seller, 3=Shipper] : ";
		getline(cin, type);
	} while
	(
		(stoi(type) != 1 && stoi(type) != 2 && stoi(type) != 3)
		&& (cout << "Invalid type." << endl)
	);

	Account* a;

	switch (stoi(type))
	{
		case 1:
			a = new Buyer;
			a->EditInfo();
			AccountProvider::GetInstance().Add(a, 'B');
			break;
		case 2:
			a = new Seller;
			a->EditInfo();
			AccountProvider::GetInstance().Add(a, 'S');
			break;
		case 3:
			a = new Shipper;
			a->EditInfo();
			AccountProvider::GetInstance().Add(a, 'H');
			break;
	}
}

//////////////////////////////////////////////////

// Unique commands
enum class Shell::c
{
	_NOT_DEFINED_,

	help,
	info,
	editinfo,
	passwd,
	// deleteaccount,

	olistall,
	olistpend,
	olookup,
	onew,
	oaccept,
	oreject,
	ostats,
	orate,

	plist,
	plisttop,
	plookup,
	psearch,
	pnew,
	pedit,
	pdelete,
	paddstock,

	sfinish
};

// Command aliases
void Shell::cMapper_Init()
{
	cMapper.clear();

	cMapper["help"] = c::help;
	cMapper["info"] = c::info;
	cMapper["editinfo"] = c::editinfo;
	cMapper["passwd"] = c::passwd;

	cMapper["olistall"] = c::olistall;
	cMapper["olistpend"] = c::olistpend;
	cMapper["olookup"] = c::olookup;
	cMapper["onew"] = c::onew;
	cMapper["oaccept"] = c::oaccept;
	cMapper["oreject"] = c::oreject;

	cMapper["plist"] = c::plist;
	cMapper["psearch"] = c::psearch;
	cMapper["pnew"] = c::pnew;
	cMapper["pedit"] = c::pedit;
	cMapper["pdelete"] = c::pdelete;
	cMapper["paddstock"] = c::paddstock;
}

// Command actions
void Shell::Interpret(string _Command)
{
	cMapper_Init();
	_Command = ToLower(_Command);

	switch (cMapper[_Command])
	{
		case c::help:		ShowHelp();	break;
		case c::info:		ShowInfo();	break;
		case c::editinfo:	EditInfo(); break;
		case c::passwd:		ChangePassword(); break;
		case c::olistall:	ListOrder();  break;
		case c::olistpend:	ListPendingOrder();  break;
		case c::olookup:	LookupOrder(); break;
		case c::onew:		CreateOrder(); break;
		case c::oaccept:	AcceptOrder(); break;
		case c::oreject:	RejectOrder(); break;
		case c::plist:		break;
		case c::psearch:	break;
		case c::pnew:		break;
		case c::pedit:		break;
		case c::pdelete:	break;
		case c::paddstock:	break;

		default: cout << "Invalid command." << endl;
	}
}

//////////////////////////////////////////////////

void Shell::Greeter()
{
	cout << "Welcome back ";
	switch (_AccountID[0])
	{
	case 'B':
		cout << AccountProvider::GetInstance().GetBuyer(_AccountID)->Name();
		break;
	case 'S':
		cout << AccountProvider::GetInstance().GetSeller(_AccountID)->Name();
		break;
	case 'H':
		cout << AccountProvider::GetInstance().GetShipper(_AccountID)->Name();
		break;
	}
	cout << "." << endl << endl;
}

void Shell::ShowHelp()
{
	// Shared
	cout << "Available commands:" << endl;
	cout << "logout : Log out" << endl;
	cout << "help   : What you're reading now." << endl;

	// Account-specific
	switch (_AccountID[0])
	{
	case 'B':
		cout << "Buyers' Commands: n/a" << endl;
		break;
	case 'S':
		cout << "Sellers' Commands: n/a" << endl;
		break;
	case 'H':
		cout << "Shippers' Commands: n/a" << endl;
		break;
	default:
		cout << "!! Unknown account type !!" << endl;
	}
}

void Shell::ShowInfo()
{
	switch (_AccountID[0])
	{
		case 'B':
			AccountProvider::GetInstance().GetBuyer(_AccountID)->GetInfo();
			break;
		case 'S':
			AccountProvider::GetInstance().GetSeller(_AccountID)->GetInfo();
			break;
		case 'H':
			AccountProvider::GetInstance().GetShipper(_AccountID)->GetInfo();
			break;
	}
}

void Shell::ChangePassword()
{

	cout << "Enter password    : ";
	string Password1 = LoginProvider::GetInstance().GetPassword();
	cout << "Re-enter password : ";
	string Password2 = LoginProvider::GetInstance().GetPassword();
	if (Password1 == Password2)
	{
		LoginProvider::GetInstance().ChangePassword(this->_AccountID, Password1);
		cout << "Password changed." << endl;
	}
	else
	{
		cout << "Passwords do not match. Operation aborted." << endl;
	}
}

void Shell::EditInfo()
{
	switch (_AccountID[0])
	{
		case 'B':
			AccountProvider::GetInstance().GetBuyer(_AccountID)->EditInfo();
			break;
		case 'S':
			AccountProvider::GetInstance().GetSeller(_AccountID)->EditInfo();
			break;
		case 'H':
			AccountProvider::GetInstance().GetShipper(_AccountID)->EditInfo();
			break;
	}
}

void Shell::ListOrder()
{
	switch (_AccountID[0])
	{
	case 'B':
		AccountProvider::GetInstance().GetBuyer(_AccountID)->ListOrder_All();
		break;

	case 'S':
		AccountProvider::GetInstance().GetSeller(_AccountID)->ListOrder_All();
		break;

	case 'H':
		AccountProvider::GetInstance().GetShipper(_AccountID)->ListOrder_All();
		break;
	}
}

void Shell::ListPendingOrder()
{
	switch (_AccountID[0])
	{
		case 'B':
			AccountProvider::GetInstance().GetBuyer(_AccountID)->ListOrder_Pending();
			break;

		case 'S':
			AccountProvider::GetInstance().GetSeller(_AccountID)->ListOrder_Pending();
			break;

		case 'H':
			AccountProvider::GetInstance().GetShipper(_AccountID)->ListOrder_Pending();
			break;
	}
}

void Shell::LookupOrder()
{
	string _OrderID;
	cout << "Order ID: "; getline(cin, _OrderID);
	Order* Result = OrderProvider::GetInstance().GetByID(_OrderID);
	if (Result != nullptr)
		Result->GetInfo();
	else
		cout << "Order not found" << endl;
}

void Shell::CreateOrder()
{
	string _ProductID;
	cout << "Product ID: "; getline(cin, _ProductID);
	AccountProvider::GetInstance().GetBuyer(_AccountID)->AddOrder(_ProductID);
}

void Shell::AcceptOrder()
{
	string _OrderID;
	cout << "Order ID: "; getline(cin, _OrderID);
	AccountProvider::GetInstance().GetSeller(_AccountID)->AcceptOrder(_OrderID);
}

void Shell::RejectOrder()
{
	string _OrderID;
	cout << "Order ID: "; getline(cin, _OrderID);
	switch (_AccountID[0]) {
	case 'B':
		AccountProvider::GetInstance().GetBuyer(_AccountID)->CancelOrder(_OrderID);
		break;
	case 'S':
		AccountProvider::GetInstance().GetSeller(_AccountID)->RejectOrder(_OrderID);
		break;
	}
}

void Shell::ListProduct()
{
	int choice;
	switch (_AccountID[0])
	{
	case 'S':
		cout << "1 : List My Products\n"
			<< "2 : List ALL Products \n";
		cout << "Search Product by (1-3) : "; cin >> choice; fflush(stdin);
		switch (choice)
		{
		case 1:
			cout << "1 : List My Products\n";
			AccountProvider::GetInstance().GetSeller(_AccountID)->ListProduct();
			break;
		case 2:
			cout << "2 : List All Products \n";
			AccountProvider::GetInstance().GetSeller(_AccountID)->ListProduct_All();
			break;
		}
		break;
	case 'B':
		//break;
	case 'H':
		//break;
	}

}

void Shell::SearchProduct()
{
	string _ProductID, _SellerID, _ProductName;
	int choice;
	switch (_AccountID[0])
	{
	case 'B':
		cout << "1 : Search Product by Product ID \n"
			<< "2 : Search Product by Seller ID \n"
			<< "3 : Search Product by Product Name \n ";
		cout << "Search Product by (1-3) : "; cin >> choice; fflush(stdin);
		switch (choice)
		{
		case 1:
			cout << "1 : Search Product by Product ID \n";
			getline(cin, _ProductID);
			AccountProvider::GetInstance().GetBuyer(_AccountID)->SearchProductByID(_ProductID);
			break;
		case 2:
			cout << "2 : Search Product by Seller ID \n";
			getline(cin, _SellerID);
			AccountProvider::GetInstance().GetBuyer(_AccountID)->SearchProductBySellerID(_SellerID);
			break;
		case 3:
			cout << "3 : Search Product by Seller ID \n";
			getline(cin, _ProductName);
			AccountProvider::GetInstance().GetBuyer(_AccountID)->SearchProductByQuery(_ProductName);
			break;
		}
	case 'S':
		//break;
	case 'H':
		//break;
	}

}

void Shell::AddProduct()
{
}

void Shell::EditProduct()
{
}

void Shell::DeleteProduct()
{
}

void Shell::AddStock()
{
}
