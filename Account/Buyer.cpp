#include "Buyer.h"

void Buyer::SearchProductByID(string _ProductID) {
	ProductProvider& _ProductProvider = ProductProvider::GetInstance();
	Product* p = _ProductProvider.GetByID(_ProductID);
	p->GetInfo();
}

void Buyer::SearchProductByName(string _ProductName)
{
	ProductProvider& _ProductProvider = ProductProvider::GetInstance();
	if ((this->GetAge()) >= 18) {
		list<Product> FilteredProduct = _ProductProvider.SearchByName(_ProductName, true);

		for (auto i =FilteredProduct.begin(); i != FilteredProduct.end(); ++i) {
			(*i).GetInfo();
			cout << endl;
		}
	}
	else
	{
		list<Product> FilteredProduct = _ProductProvider.SearchByName(_ProductName, false);

		for (auto i = FilteredProduct.begin(); i != FilteredProduct.end(); ++i) {
			(*i).GetInfo();
			cout << endl;
		}
	}
}

void Buyer::Rate(string _OrderID)
{
	ProductProvider& _ProductProvider = ProductProvider::GetInstance();
	OrderProvider& _OrderProvider = OrderProvider::GetInstance();
	AccountProvider& _AccountProvider = AccountProvider::GetInstance();
	Order* _Order = _OrderProvider.GetByID(_OrderID);
	int rate;

	if (_Order->Status() != 3) {
		cout << " Your Order Is Processing " << endl;
		return;
	}
	cout << "How satisfied are you with this product? (1-5) : ";
	cin >> rate;
	Product* _Product = _ProductProvider.GetByID(_Order->ProductID());
	_Product->Rate(rate);

	cout << "How satisfied are you with this seller? (1-5) : ";
	cin >> rate;
	Seller* _Seller = _AccountProvider.FindSeller(_Order->SellerID());
	_Seller->Rate(rate);
	cout << "Thanks for your choices" << endl;
}