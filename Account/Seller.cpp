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

void Seller::GetProductByID(string _ProductID)
{
	if (!ProductProvider::isRelated(this->ID(), _ProductID))
	{
		cout << "Product not found" << endl;
		return;
	}
	ProductProvider::GetInstance().GetByID(_ProductID)->GetInfo();
}

void Seller::AddProduct()
{
	Product _Product;
	_Product.SellerID(this->ID());
	this->EditProduct(_Product.ID());
	string amount;
	cout << "Add stock: "; getline(cin, amount); _Product.AddStock(stoi(amount));
	ProductProvider::GetInstance().Add(_Product);
}

void Seller::EditProduct(string _ProductID)
{
	if (!ProductProvider::isRelated(this->ID(), _ProductID))
	{
		cout << "Product not found" << endl;
		return;
	}

	ProductProvider::GetInstance().GetByID(_ProductID)->EditInfo();
}

void Seller::DeleteProduct(string _ProductID)
{
	if (!ProductProvider::isRelated(this->ID(), _ProductID))
	{
		cout << "Product not found" << endl;
		return;
	}

	ProductProvider::GetInstance().Delete(_ProductID);
}

void Seller::AddStock(string _ProductID, int32_t _Amount)
{
	if (!ProductProvider::isRelated(this->ID(), _ProductID))
	{
		cout << "Product not found" << endl;
		return;
	}

	ProductProvider::GetInstance().GetByID(_ProductID)->AddStock(_Amount);
}

void Seller::ListShippers()
{
	list<Shipper*> AvailableShipper = AccountProvider::GetInstance().ListShippers();
	for (auto i = AvailableShipper.begin(); i != AvailableShipper.end(); ++i)
		cout << (**i).ID() << " (" << (**i).Name() << ")" << endl;
}

void Seller::AcceptOrder(string _OrderID)
{
	if (!OrderProvider::isRelated(this->ID(), _OrderID))
	{
		cout << "Order not found" << endl;
		return;
	}

	Order* _Order = OrderProvider::GetInstance().GetByID(_OrderID);
	
	if (_Order->Status() != SELLER_PENDING)
	{
		cout << "This order is waiting for delivery, completed or cancelled." << endl;
		return;
	}

	ListShippers();

	string _ShipperID; 
	do
	{
		cout << "Enter shipper ID: ";
		getline(cin, _ShipperID);
	} while
	(
		(AccountProvider::GetInstance().GetShipper(_ShipperID) == nullptr)
		&& (cout << "Invalid shipper ID." << endl)
	);
	_Order->ShipperID(_ShipperID);

	string _ShippingFee;
	do
	{
		cout << "Shipping fee: ";
		getline(cin, _ShippingFee);
	} while
	(
		(stoll(_ShippingFee) < 0)
		&& (cout << "Invalid shipping fee." << endl)
	);
	_Order->ShippingFee(stoll(_ShippingFee));

	string _PriceCoeff;
	do
	{
		cout << "% Sale (0 - 100): ";
		getline(cin, _PriceCoeff);
	} while
	(
		(stod(_PriceCoeff) < 0 || stod(_PriceCoeff) > 100)
		&& (cout << "Invalid price coefficient." << endl)
	);
	_Order->PriceCoeff(1 - stod(_PriceCoeff) / 100);

	string _Note;
	cout << "Note (optional): ";
	getline(cin, _Note);
	_Order->Note(_Note);

	_Order->Status(BUYER_PENDING);
}

void Seller::RejectOrder(string _OrderID)
{
	if (!OrderProvider::isRelated(this->ID(), _OrderID))
	{
		cout << "Order not found." << endl;
		return;
	}

	Order* _Order = OrderProvider::GetInstance().GetByID(_OrderID);

	if (_Order->Status() != SELLER_PENDING)
	{
		cout << "This order is waiting for delivery, completed or cancelled." << endl;
		return;
	}

	string _Note;
	cout << "Note (i.e. why you've rejected this order): ";
	getline(cin,_Note);
	_Order->Note(_Note);

	_Order->Status(SELLER_CANCELLED);
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

void Seller::CancelOrder(string _OrderID)
{
	Order* _Order = OrderProvider::GetInstance().GetByID(_OrderID);
	if (_Order == nullptr) {
		cout << "Order does not exist." << endl;
		return;
	}
	if (_Order->Status() == SELLER_PENDING) {
		_Order->Status(SELLER_CANCELLED);
	}
	else {
		cout << "Can not cancel order now" << endl;
		return;
	}
}
