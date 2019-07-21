#include "Buyer.h"
#include "AccountProvider.h"
#include "../Product/ProductProvider.h"
#include "../Order/OrderProvider.h"

void Buyer::SearchProductByID(string _ProductID)
{
	Product* p = ProductProvider::GetInstance().GetByID(_ProductID);
	if (p != nullptr) p->GetInfo();
}

void Buyer::SearchProductByName(string _ProductName)
{
	list<Product> FilteredProduct = ProductProvider::GetInstance().SearchByName(_ProductName, ((this->GetAge()) >= 18));
	for (auto i = FilteredProduct.begin(); i != FilteredProduct.end(); ++i)
	{
		(*i).GetInfo();
		cout << endl;
	}
}

void Buyer::CreateOrder()
{
	Order newOrder;
	string s;
	cout << "Product ID: ";
	getline(cin, s);
	Product* x = ProductProvider::GetInstance().GetByID(s);
	if (x == nullptr) {
		cout << "Product does not exist." << endl;
		return;
	}
	
	int amount;
	cin >> amount;
	if (x->Stock() < amount) {
		cout << "There are not enough stock in the storage." << endl;
		return;
	}
	newOrder.Quantity(amount);

	list<Order> FilteredOrder = OrderProvider::GetInstance().Search(this->ID());
	int64_t MoneytoPay = 0;
	for (auto i = FilteredOrder.begin(); i != FilteredOrder.end(); ++i) {
		MoneytoPay += (*i).TotalPrice();
	}
	MoneytoPay += newOrder.TotalPrice();

	if (MoneytoPay > this->Balance()) {
		cout << "There is not enough money for you to create this order." << endl;
		return;
	}

	newOrder.ProductID(s);
	newOrder.BuyerID(this->ID());
	newOrder.SellerID(x->SellerID());
	newOrder.Status(SELLER_PENDING);

	Date today;
	today.Today();
	newOrder.OrderDate(today);

	OrderProvider::GetInstance().Add(newOrder);
}

void Buyer::CancelOrder(string _OrderID)
{
	Order* _Order = OrderProvider::GetInstance().GetByID(_OrderID);

	if (_Order == nullptr) {
		cout << "Order does not exist." << endl;
		return;
	}

	if (_Order->Status() == SELLER_PENDING) {
		_Order->Status(BUYER_CANCELLED);
	}
	else {
		cout << "Can not cancel order now" << endl;
		return;
	}
}

void Buyer::Rate(string _OrderID)
{
	Order* _Order = OrderProvider::GetInstance().GetByID(_OrderID);

	if (_Order->Status() != COMPLETED)
	{
		cout << "Your Order Is Processing" << endl;
		return;
	}

	string _Rate;

	do
	{
		cout << "How satisfied are you with this product? (1-5) : ";
		getline(cin, _Rate);
	} while (
		(stoi(_Rate) < 1 || stoi(_Rate) > 5)
		&& (cout << "Invalid range." << endl)
	);
	ProductProvider::GetInstance().GetByID(_Order->ProductID())->Rate(stoi(_Rate));

	do
	{
		cout << "How satisfied are you with this seller? (1-5) : ";
		getline(cin, _Rate);
	} while (
		(stoi(_Rate) < 1 || stoi(_Rate) > 5)
		&& (cout << "Invalid range." << endl)
	);
	AccountProvider::GetInstance().FindSeller(_Order->SellerID())->Rate(stoi(_Rate));
	
	cout << "Thanks for your choices" << endl;
}
