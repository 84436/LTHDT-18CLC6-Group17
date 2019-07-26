#include "Buyer.h"
#include "AccountProvider.h"
#include "../Product/ProductProvider.h"
#include "../Order/OrderProvider.h"

void Buyer::ListOrder_Pending()
{
	list<Order> FilteredOrders = OrderProvider::GetInstance().ListByAccountID(this->ID());

	FilteredOrders.remove_if(OrderProvider::isCompleted);

	cout << "Total pending order count: " << FilteredOrders.size() << endl;
	for (auto i = FilteredOrders.begin(); i != FilteredOrders.end(); ++i)
	{
		cout << (*i).ID() << " : " << (*i).Status_String() << endl;
	}
}

void Buyer::GetProductByID(string _ProductID)
{
	Product* _Product = ProductProvider::GetInstance().GetByID(_ProductID);
	if (_Product == nullptr)
	{
		cout << "Product not found." << endl;
		return;
	}
	_Product->GetInfo();
}

void Buyer::ListProductBySellerID(string _SellerID)
{
	list<Product> FilteredProducts = ProductProvider::GetInstance().ListBySellerID(_SellerID, ((this->GetAge()) >= 18));
	for (auto i = FilteredProducts.begin(); i != FilteredProducts.end(); ++i)
	{
		cout << (*i).ID() << ": SellerID = " << (*i).SellerID() << "; Name = " << (*i).Name() << endl;
	}
}

void Buyer::ListProductByQuery(string _ProductName)
{
	if (isEmptyString(_ProductName))
	{
		cout << "Empty query." << endl;
		return;
	}
	list<Product> FilteredProducts = ProductProvider::GetInstance().ListByQuery(_ProductName, ((this->GetAge()) >= 18));
	for (auto i = FilteredProducts.begin(); i != FilteredProducts.end(); ++i)
	{
		cout << (*i).ID() << ": SellerID = " << (*i).SellerID() << "; Name = " << (*i).Name() << endl;
	}
}

void Buyer::AddOrder(string _ProductID)
{
	Order newOrder;
	
	Product* x = ProductProvider::GetInstance().GetByID(_ProductID);
	if (x == nullptr) {
		cout << "Product does not exist." << endl;
		return;
	}

	newOrder.ProductID(_ProductID);
	newOrder.BuyerID(this->ID());
	newOrder.SellerID(x->SellerID());
	
	string amount;
	do {
		cout << "Amount: "; getline(cin, amount);
	} while
	(
		(stoi(amount) <= 0)
		&& (cout << "Invalid amount." << endl)
	);

	if (x->Stock() < stoi(amount)) {
		cout << "There are not enough stock in the storage." << endl;
		return;
	}
	newOrder.Quantity(stoi(amount));

	list<Order> FilteredOrder = OrderProvider::GetInstance().ListByAccountID(this->ID());
	int64_t MoneytoPay = 0;
	for (auto i = FilteredOrder.begin(); i != FilteredOrder.end(); ++i) {
		if ((*i).Status() != COMPLETED)
			MoneytoPay += (*i).TotalPrice();
	}
	MoneytoPay += newOrder.TotalPrice();

	if (MoneytoPay > this->Balance()) {
		cout << "There is not enough money for you to create this order." << endl;
		return;
	}

	newOrder.Status(SELLER_PENDING);

	newOrder.OrderDate(Date::Today());

	OrderProvider::GetInstance().Add(newOrder);
}

void Buyer::AcceptOrder(string _OrderID)
{
	if (!OrderProvider::isRelated(this->ID(), _OrderID))
	{
		cout << "Order not found." << endl;
		return;
	}

	Order* _Order = OrderProvider::GetInstance().GetByID(_OrderID);

	if (_Order->Status() == BUYER_PENDING) {
		_Order->Status(SHIPPING_PENDING);
	}
	else {
		cout << "Can not accept order now" << endl;
		return;
	}
}

void Buyer::CancelOrder(string _OrderID)
{
	if (!OrderProvider::isRelated(this->ID(), _OrderID))
	{
		cout << "Order not found." << endl;
		return;
	}

	Order* _Order = OrderProvider::GetInstance().GetByID(_OrderID);

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
	if (!OrderProvider::isRelated(this->ID(), _OrderID))
	{
		cout << "Order not found." << endl;
		return;
	}
	
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
	AccountProvider::GetInstance().GetSeller(_Order->SellerID())->Rate(stoi(_Rate));
	
	cout << "Thanks for your choices" << endl;
}
