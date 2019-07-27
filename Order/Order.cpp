#include "Order.h"

Order::Order(const Order& _Order)
{
	this->_ID = _Order._ID;
	this->_ProductID = _Order._ProductID;
	this->_SellerID = _Order._SellerID;
	this->_BuyerID = _Order._BuyerID;
	this->_ShipperID = _Order._ShipperID;
	this->_PriceCoeff = _Order._PriceCoeff;
	this->_OrderDate = _Order._OrderDate;
	this->_ShippingDate = _Order._ShippingDate;
	this->_ShippingFee = _Order._ShippingFee;
	this->_Status= _Order._Status;
	this->_Note = _Order._Note;
	this->_Quantity = _Order._Quantity;
}

string Order::Status_String()
{
	switch (this->Status())
	{
		case BUYER_CANCELLED:		return "Cancelled by buyer";
		case SELLER_CANCELLED:		return "Cancelled by seller";
		case BUYER_PENDING:			return "Waiting for buyer's approval";
		case SELLER_PENDING:		return "Waiting for seller's approval";
		case SHIPPING_PENDING:		return "Delivering";
		case COMPLETED:				return "Completed";
		default:					return "Unknown status";
	}
}

int64_t Order::TotalPrice()
{
	return (int64_t)(_PriceCoeff * ProductProvider::GetInstance().GetByID(_ProductID)->Price() * _Quantity + _ShippingFee);
}

void Order::GetInfo()
{
	cout << "ID            : " << this->ID() << endl;
	cout << "Product       : " << (ProductProvider::GetInstance().GetByID(this->ProductID()) == nullptr ?  "n/a" : this->ProductID() + " (" + ProductProvider::GetInstance().GetByID(this->ProductID())->Name() + ")") << endl;
	cout << "Seller        : " << (AccountProvider::GetInstance().GetSeller(this->SellerID()) == nullptr ? "n/a" : this->SellerID() + " (" + AccountProvider::GetInstance().GetSeller(this->SellerID())->Name() + ")") << endl;
	cout << "Buyer         : " << (AccountProvider::GetInstance().GetBuyer(this->BuyerID()) == nullptr ? "n/a" : this->BuyerID() + " (" + AccountProvider::GetInstance().GetBuyer(this->BuyerID())->Name() + ")") << endl;
	cout << "Shipper       : " << (AccountProvider::GetInstance().GetShipper(this->ShipperID()) == nullptr ? "n/a" : this->ShipperID() + " (" + AccountProvider::GetInstance().GetShipper(this->ShipperID())->Name() + ")") << endl;
	cout << "Quantity      : " << this->Quantity() << endl;
	cout << "Shipping fee  : " << (AccountProvider::GetInstance().GetShipper(this->ShipperID()) == nullptr ? "n/a" : to_string(this->ShippingFee())) << endl;
	cout << "Total price   : " << (AccountProvider::GetInstance().GetShipper(this->ShipperID()) == nullptr ? "n/a" : to_string(this->TotalPrice())) << endl;
	cout << "Ordered date  : " << (int)this->OrderDate().Year << '-' << (int)this->OrderDate().Month << '-' << (int)this->OrderDate().Day << endl;
	cout << "Shipping date : " << (this->Status() != COMPLETED ? "n/a" : to_string((int)this->ShippingDate().Year) + '-' + to_string((int)this->ShippingDate().Month) + '-' + to_string((int)this->ShippingDate().Day)) << endl;
	cout << "Status        : " << this->Status_String() << endl;
	cout << "Note          : " << (this->Note().length() == 0 ? "n/a" : this->Note()) << endl;
}