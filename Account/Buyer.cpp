#include "Buyer.h"

void Buyer::SearchProduct(string _name)
{
	if (YOB() >= 18) {
		_ProductProvider->SearchByName(_name , true);
	}
	else
	{
		_ProductProvider->SearchByName(_name, false);
	}
}

void Buyer::Rate(Order& _order)
{
	AccountProvider _AccountProvider = AccountProvider::GetInstance();
	int n;
	if ( _order.Status() != 3) {
		cout << " Your Order Is Processing " << endl;
		return;
	}
	cout << "This Product Satisfy You ? (1-5) : ";
	cin >> n;
	Product * _product = _ProductProvider->GetByID(_order.ID());
	_product->Rate(n);
	cout << "This Seller Satisfy You ? (1-5) : ";
	cin >> n;
	Seller* _seller = _AccountProvider.FindSeller(_order.SellerID());
	_seller->Rate(n);
	cout << "Thanks for your choices " << endl;
}
