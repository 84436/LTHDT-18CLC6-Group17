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
	// Tạo order (hỏi Product ID, số lượng)
	// Xét ví của Buyer
		// OrderProvider: lấy các order chưa hoàn thành của mình
		// Cộng dồn số tiền trước khi xét ví
	// OrderProvider: lấy order Add() vào
}

void Buyer::CancelOrder(string _OrderID)
{
	// OrderProvider: ID -> Order*
	// Order*: xét status
		// Nếu status đang là "Chờ Seller chấp nhận"
			// Order*: đổi status thành "Buyer hủy"
		// Nếu status đang là "Chờ Shipper giao"
			// Nope, quá trễ rồi.
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
