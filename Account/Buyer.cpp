#include "Buyer.h"
#include "AccountProvider.h"
#include "../Product/ProductProvider.h"
#include "../Order/OrderProvider.h"

void Buyer::ListOrder_Pending()
{
	list<Order> FilteredOrders = OrderProvider::GetInstance().ListByAccountID(this->ID());

	FilteredOrders.remove_if(OrderProvider::isNotPending_Buyer);

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
	if (!(this->GetAge() >= 18) && _Product->isR18())
	{
		cout << "This product is rated 18+ / Mature Only." << endl;
		return;
	}
	_Product->GetInfo();
}

void Buyer::ListProductBySellerID(string _SellerID)
{
	list<Product> FilteredProducts = ProductProvider::GetInstance().ListBySellerID(_SellerID, (this->GetAge() >= 18));
	if (FilteredProducts.empty())
	{
		cout << "No products found." << endl;
		cout << "This can be because seller..." << endl;
		cout << "  - does not exist." << endl;
		cout << "  - has not added any product." << endl;
		cout << "  - only sells rate 18+ / Mature Only products." << endl;
		return;
	}
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
	if (FilteredProducts.empty())
	{
		cout << "No products found." << endl;
		cout << "This can be because..." << endl;
		cout << "  - There are no products whose name or category (partially) match your query." << endl;
		cout << "  - You are not allowed to view rate 18+ / Mature Only products." << endl;
		return;
	}
	for (auto i = FilteredProducts.begin(); i != FilteredProducts.end(); ++i)
	{
		cout << (*i).ID() << ": SellerID = " << (*i).SellerID() << "; Name = " << (*i).Name() << endl;
	}
}

void Buyer::AddOrder(string _ProductID)
{
	Product* _Product = ProductProvider::GetInstance().GetByID(_ProductID);
	if (_Product == nullptr)
	{
		cout << "Product does not exist." << endl;
		return;
	}
	if (!(this->GetAge() >= 18) && _Product->isR18())
	{
		cout << "This product is rated 18+ / Mature Only." << endl;
		return;
	}

	Order NewOrder;

	NewOrder.ProductID(_ProductID);
	NewOrder.BuyerID(this->ID());
	NewOrder.SellerID(_Product->SellerID());
	NewOrder.OrderDate(Date::Today());
	NewOrder.Status(SELLER_PENDING);
	
	string _Quantity;
	while (true)
	{
		cout << "Quantity: ";
		getline(cin, _Quantity);
		if (stoi(_Quantity) <= 0)
		{
			cout << "Invalid amount." << endl;
			continue;
		}
		if (stoi(_Quantity) > _Product->Stock())
		{
			cout << "Not enough stock." << endl;
			continue;
		}
		break;
	}
	NewOrder.Quantity(stoi(_Quantity));

	int64_t MoneytoPay = 0;
	list<Order> FilteredOrder = OrderProvider::GetInstance().ListByAccountID(this->ID());
	FilteredOrder.remove_if(OrderProvider::isNotPending_Buyer);
	for (auto i = FilteredOrder.begin(); i != FilteredOrder.end(); ++i)
	{
		MoneytoPay += (*i).TotalPrice();
	}
	MoneytoPay += NewOrder.TotalPrice();
	if (MoneytoPay > this->Balance())
	{
		cout << "There is not enough money for you to create this order." << endl;
		return;
	}

	string _Note;
	cout << "Note (optional): ";
	getline(cin, _Note);
	NewOrder.Note(_Note);

	OrderProvider::GetInstance().Add(NewOrder);
}

void Buyer::AcceptOrder(string _OrderID)
{
	if (!OrderProvider::isRelated(this->ID(), _OrderID))
	{
		cout << "Order not found." << endl;
		return;
	}

	Order* _Order = OrderProvider::GetInstance().GetByID(_OrderID);

	if (_Order->Status() == BUYER_PENDING)
	{
		_Order->Status(SHIPPING_PENDING);
	}
	else
	{
		cout << "You cannot accept an order in the following conditions:" << endl;
		cout << "  - The order was previously rejected by the seller or yourself." << endl;
		cout << "  - The order has already been completed." << endl;
		return;
	}
}

void Buyer::RejectOrder(string _OrderID)
{
	if (!OrderProvider::isRelated(this->ID(), _OrderID))
	{
		cout << "Order not found." << endl;
		return;
	}

	Order* _Order = OrderProvider::GetInstance().GetByID(_OrderID);

	if (_Order->Status() == BUYER_PENDING)
	{
		string _Note;
		cout << "Note (optional): ";
		getline(cin, _Note);
		_Order->Note(_Note);

		_Order->Status(BUYER_CANCELLED);
	}
	else {
		cout << "You cannot reject an order in the following conditions:" << endl;
		cout << "  - The order was previously rejected by the seller or yourself." << endl;
		cout << "  - The order is waiting for delivery." << endl;
		cout << "  - The order has already been completed." << endl;
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
		cout << "You can only rate an order once it has been completed." << endl;
		return;
	}

	string _Rate;

	do
	{
		cout << "How satisfied are you with this product? (1-5) : ";
		getline(cin, _Rate);
	}
	while
	(
		(stoi(_Rate) < 1 || stoi(_Rate) > 5)
		&& (cout << "Invalid range." << endl)
	);
	ProductProvider::GetInstance().GetByID(_Order->ProductID())->Rate(stoi(_Rate));

	do
	{
		cout << "How satisfied are you with this seller? (1-5) : ";
		getline(cin, _Rate);
	}
	while
	(
		(stoi(_Rate) < 1 || stoi(_Rate) > 5)
		&& (cout << "Invalid range." << endl)
	);
	AccountProvider::GetInstance().GetSeller(_Order->SellerID())->Rate(stoi(_Rate));
	
	cout << "Thank you for rating." << endl;
}
