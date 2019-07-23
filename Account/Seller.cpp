#include "Seller.h"
#include "AccountProvider.h"
#include "../Product/ProductProvider.h"
#include "../Order/OrderProvider.h"

void Seller::ListOrder_Pending()
{
	list<Order> FilteredOrders = OrderProvider::GetInstance().ListByAccountID(this->ID());

	FilteredOrders.remove_if(OrderProvider::isNotSellerPending);

	cout << "Total pending order count: " << FilteredOrders.size() << endl;
	for (auto i = FilteredOrders.begin(); i != FilteredOrders.end(); ++i)
	{
		cout << (*i).ID() << " : " << (*i).Status_String() << endl;
	}
}

void Seller::GetInfo()
{
	Account::GetInfo();
	cout << "Rating        : " << this->GetRate() << endl;
}

void Seller::ListProduct()
{
	list<Product> FilteredProducts = ProductProvider::GetInstance().ListBySellerID(this->ID(), true);
	for (auto i = FilteredProducts.begin(); i != FilteredProducts.end(); ++i)
	{
		cout << (*i).ID() << ": Name = " << (*i).Name() << endl;
	}
}

void Seller::AddProduct()
{
	Product p;
	p.SellerID(this->ID());
	this->EditProduct(p.ID());
	string amount;
	cout << "Add stock: "; getline(cin, amount); p.AddStock(stoi(amount));
	ProductProvider::GetInstance().Add(p);
}

void Seller::EditProduct(string _ProductID)
{
	Product* p = ProductProvider::GetInstance().GetByID(_ProductID);
	if (p == nullptr) {
		cout << "Product does not exist" << endl;
		return;
	}
	p->EditInfo();
}

void Seller::DeleteProduct(string _ProductID)
{
	ProductProvider::GetInstance().Delete(_ProductID);
}

void Seller::AcceptOrder(string _OrderID)
{
	// Set price coeff
	// Set shipping fee
	// Set note (optional)
	OrderProvider::GetInstance().GetByID(_OrderID)->Status(SHIPPING_PENDING);
}

void Seller::RejectOrder(string _OrderID)
{
	// Hỏi lý do tại sao (ghi vào Note)
	OrderProvider::GetInstance().GetByID(_OrderID)->Status(SELLER_CANCELLED);
}

vector<int16_t> Seller::RatingArray()
{
	return Rating;
}

void Seller::RatingArray(int16_t _1, int16_t _2, int16_t _3, int16_t _4, int16_t _5)
{
	this->Rating[0] = _1;
	this->Rating[1] = _2;
	this->Rating[2] = _3;
	this->Rating[3] = _4;
	this->Rating[4] = _5;
}

void Seller::Rate(int _score)
{
	Rating[_score - 1]++;
}

float Seller::GetRate()
{
	return (float)(1*Rating[0] + 2*Rating[1] + 3*Rating[2] + 4*Rating[3] + 5*Rating[4]) / (float)(Rating[0] + Rating[1] + Rating[2] + Rating[3] + Rating[4]);
}

void Seller::StatsByMonth(uint8_t _Month)
{
	if (_Month < 1 || _Month > 12)
	{
		cout << "Invalid month" << endl;
		return;
	}

	list<Order> FilteredOrders = OrderProvider::GetInstance().ListByAccountID(this->ID());
	for (auto i = FilteredOrders.begin(); i != FilteredOrders.end(); ++i)
	{
		if ((*i).ShippingDate().Month != _Month) FilteredOrders.erase(i);
	}

	// What month is it?

	// Total $
	int64_t Total = 0;
	for (auto i = FilteredOrders.begin(); i != FilteredOrders.end(); ++i)
	{
		Total += ((*i).TotalPrice() - (*i).ShippingFee());
	}
	cout << "Total $ = " << Total << endl;

	// Product count : std::map

	// Best seller
}
