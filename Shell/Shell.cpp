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
	// Undefined command
	_NOT_DEFINED_,

	// Account
	help,
	info,
	editinfo,
	passwd,
	wcheck,
	wdeposit,
	wwithdraw,

	// Product
	plookup,
	plist,
	plistbyseller,
	psearch,
	pnew,
	pedit,
	pdelete,
	paddstock,

	// Order
	olookup,
	olist,
	olistpend,
	onew,
	oaccept,
	oreject,
	orate,

	// Seller's/Shipper's stats
	stats,

	// Shipper-related
	hlist,
	ship
};

// Command "mapper"
void Shell::cMapper_Init()
{
	cMapper.clear();

	// ALL - Account info
	cMapper["help"] = c::help;
	cMapper["info"] = c::info;
	cMapper["editinfo"] = c::editinfo;
	cMapper["passwd"] = c::passwd;
	cMapper["balance"] = c::wcheck;

	// ALL - Orders
	cMapper["olist"] = c::olist;
	cMapper["olistpend"] = c::olistpend;
	cMapper["olookup"] = c::olookup;

	switch (_AccountID[0])
	{
		case 'B':
			// BUYER - Products
			cMapper["plookup"] = c::plookup;
			cMapper["psearch"] = c::psearch;
			cMapper["plistbyseller"] = c::plistbyseller;

			// BUYER - Orders
			cMapper["onew"] = c::onew;
			cMapper["oaccept"] = c::oaccept;
			cMapper["oreject"] = c::oreject;
			cMapper["topup"] = c::wdeposit;
			break;

		case 'S':
			// SELLER - Account
			cMapper["withdraw"] = c::wwithdraw;
			cMapper["stats"] = c::stats;

			// SELLER - Products
			cMapper["plookup"] = c::plookup;
			cMapper["plist"] = c::plist;
			cMapper["pnew"] = c::pnew;
			cMapper["pedit"] = c::pedit;
			cMapper["pdelete"] = c::pdelete;
			cMapper["paddstock"] = c::paddstock;

			// SELLER - Orders
			cMapper["oaccept"] = c::oaccept;
			cMapper["oreject"] = c::oreject;
			cMapper["hlist"] = c::hlist;
			break;

		case 'H':
			// SHIPPER - Account
			cMapper["stats"] = c::stats;
			cMapper["withdraw"] = c::wwithdraw;

			// SHIPPER - Orders
			cMapper["ship"] = c::ship;
			break;
	}
}

// Command actions
void Shell::Interpret(string _Command)
{
	cMapper_Init();
	_Command = ToLower(_Command);

	switch (cMapper[_Command])
	{
		case c::help:			ShowHelp();					break;
		case c::info:			ShowInfo();					break;
		case c::editinfo:		EditInfo();					break;
		case c::passwd:			ChangePassword();			break;
		case c::wdeposit:		WalletTopUp();				break;
		case c::wwithdraw:		WalletWithdraw();			break;
		case c::wcheck:			WalletCheck();				break;

		case c::plist:			ListProduct();				break;
		case c::plistbyseller:	ListProductBySeller();		break;
		case c::plookup:		LookupProduct();			break;
		case c::psearch:		SearchProduct();			break;
		case c::pnew:			AddProduct();				break;
		case c::pedit:			EditProduct();				break;
		case c::pdelete:		DeleteProduct();			break;
		case c::paddstock:		AddStock();					break;

		case c::olist:			ListOrder();				break;
		case c::olistpend:		ListPendingOrder();			break;
		case c::olookup:		LookupOrder();				break;
		case c::onew:			CreateOrder();				break;
		case c::oaccept:		AcceptOrder();				break;
		case c::oreject:		RejectOrder();				break;
		case c::orate:			RateOrder();				break;

		case c::hlist:			ListShippers();				break;
		case c::ship:			Ship();						break;
		case c::stats:			Stats();					break;

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
	cout
		<< "Available commands" << endl
		<< "logout        : Log out" << endl
		<< "help          : What you're reading now" << endl
		<< "info          : View account info" << endl
		<< "editinfo      : Edit account info" << endl
		<< "passwd        : Change password" << endl
		<< "balance       : Check wallet balance" << endl
		<< "olookup       : Show details of an order" << endl
		<< "olist         : List orders" << endl
		<< "olistpend     : List pending orders" << endl
		<< endl;

	// Account-specific
	switch (_AccountID[0])
	{
		case 'B':
			cout
				<< "psearch       : Search products" << endl
				<< "plistbyseller : List products of a specific seller" << endl
				<< "plookup       : Show details of a product" << endl
				<< "onew          : Create a new order (Buy a product)" << endl
				<< "oaccept       : Accept an order (after being quoted by seller)" << endl
				<< "oreject       : Reject/Cancel an order" << endl
				<< "orate         : Rate an order" << endl
				<< endl;
			break;
		case 'S':
			cout
				<< "plist         : List all products that you own" << endl
				<< "plookup       : Show details of a product that you own" << endl
				<< "pnew          : Add a new product" << endl
				<< "pedit         : Edit a product" << endl
				<< "pdelete       : Remove a product" << endl
				<< "paddstock     : Re-stock a product" << endl
				<< "oaccept       : Accept an order from the buyers" << endl
				<< "oreject       : Reject an order" << endl
				<< "hlist         : List all shippers available" << endl
				<< "stats         : Get statistics by month" << endl
				<< endl;
			break;
		case 'H':
			cout
				<< "ship          : Ship a product" << endl
				<< "stats         : Get statistics by month" << endl
				<< endl;
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

void Shell::WalletCheck()
{
	switch (_AccountID[0])
	{
		case 'B':
			AccountProvider::GetInstance().GetBuyer(_AccountID)->CheckBalance();
			break;

		case 'S':
			AccountProvider::GetInstance().GetSeller(_AccountID)->CheckBalance();
			break;

		case 'H':
			AccountProvider::GetInstance().GetShipper(_AccountID)->CheckBalance();
			break;
	}
}

void Shell::WalletWithdraw()
{
	string _Amount;
	do
	{
		cout << "Amount: ";
		getline(cin, _Amount);
	} while
	(
		(stoll(_Amount) <= 0)
		&& (cout << "Invalid amount" << endl)
	);
	switch (_AccountID[0])
	{
		case 'S':
			AccountProvider::GetInstance().GetSeller(_AccountID)->Withdraw(stoll(_Amount));
			break;

		case 'H':
			AccountProvider::GetInstance().GetShipper(_AccountID)->Withdraw(stoll(_Amount));
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
	switch (_AccountID[0])
	{
	case 'B':
		AccountProvider::GetInstance().GetBuyer(_AccountID)->GetOrderByID(_OrderID);
		break;

	case 'S':
		AccountProvider::GetInstance().GetSeller(_AccountID)->GetOrderByID(_OrderID);
		break;

	case 'H':
		AccountProvider::GetInstance().GetShipper(_AccountID)->GetOrderByID(_OrderID);
		break;
	}
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
	switch (_AccountID[0]) {
	case 'B':
		AccountProvider::GetInstance().GetBuyer(_AccountID)->AcceptOrder(_OrderID);
		break;
	case 'S':
		AccountProvider::GetInstance().GetSeller(_AccountID)->AcceptOrder(_OrderID);
		break;
	}
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

void Shell::RateOrder()
{
	string _OrderID;
	cout << "Order ID: "; getline(cin, _OrderID);
	AccountProvider::GetInstance().GetBuyer(_AccountID)->Rate(_OrderID);
}

void Shell::WalletTopUp()
{
	string _Amount;
	do
	{
		cout << "Amount: ";
		getline(cin, _Amount);
	} while
	(
		(stoll(_Amount) <= 0)
		&& (cout << "Invalid amount" << endl)
	);
	AccountProvider::GetInstance().GetBuyer(_AccountID)->Deposit(stoll(_Amount));
}

void Shell::ListProduct()
{
	AccountProvider::GetInstance().GetSeller(_AccountID)->ListProduct();
}

void Shell::LookupProduct()
{
	string _ProductID;
	cout << "Product ID: "; getline(cin, _ProductID);
	switch (_AccountID[0]) {
	case 'B':
		AccountProvider::GetInstance().GetBuyer(_AccountID)->GetProductByID(_ProductID);
		break;
	case 'S':
		AccountProvider::GetInstance().GetSeller(_AccountID)->GetProductByID(_ProductID);
		break;
	}
}

void Shell::SearchProduct()
{
	string _Query;
	cout << "Query: "; getline(cin, _Query);
	AccountProvider::GetInstance().GetBuyer(_AccountID)->ListProductByQuery(_Query);
}

void Shell::ListProductBySeller()
{
	string _SellerID;
	cout << "Seller ID: "; getline(cin, _SellerID);
	AccountProvider::GetInstance().GetBuyer(_AccountID)->ListProductBySellerID(_SellerID);
}

void Shell::AddProduct()
{
	AccountProvider::GetInstance().GetSeller(_AccountID)->AddProduct();
}

void Shell::EditProduct()
{
	string _ProductID;
	cout << "Product ID: "; getline(cin, _ProductID);
	AccountProvider::GetInstance().GetSeller(_AccountID)->EditProduct(_ProductID);
}

void Shell::DeleteProduct()
{
	string _ProductID;
	cout << "Product ID: "; getline(cin, _ProductID);
	AccountProvider::GetInstance().GetSeller(_AccountID)->DeleteProduct(_ProductID);
}

void Shell::AddStock()
{
	string _ProductID;
	cout << "Product ID: "; getline(cin, _ProductID);

	string _Amount;
	do
	{
		cout << "Amount: ";
		getline(cin, _Amount);
	} while
	(
		(stoi(_Amount) <= 0)
		&& (cout << "Invalid amount" << endl)
	);

	AccountProvider::GetInstance().GetSeller(_AccountID)->AddStock(_ProductID, stoi(_Amount));
}

void Shell::ListShippers()
{
	AccountProvider::GetInstance().GetSeller(_AccountID)->ListShippers();
}

void Shell::Ship()		
{
	string _OrderID;
	cout << "Order ID: "; getline(cin, _OrderID);
	AccountProvider::GetInstance().GetShipper(_AccountID)->FinishOrder(_OrderID);
}

void Shell::Stats()
{
	string _Month;
	do {
		cout << "Month: "; getline(cin, _Month);
	} while
	(
		(stoi(_Month) < 1 || stoi(_Month) > 12)
			&& (cout << "Invalid month." << endl)
	);
	switch (_AccountID[0]) {
	case 'S':
		AccountProvider::GetInstance().GetSeller(_AccountID)->StatsByMonth(stoi(_Month));
		break;
	case 'H':
		AccountProvider::GetInstance().GetShipper(_AccountID)->StatsByMonth(stoi(_Month));
		break;
	}
}
