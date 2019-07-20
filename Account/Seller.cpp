#include "Seller.h"
#include "AccountProvider.h"
#include "../Product/ProductProvider.h"
#include "../Order/OrderProvider.h"

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
	// Set shipping fee
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