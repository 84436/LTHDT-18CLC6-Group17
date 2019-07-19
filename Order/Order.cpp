#include "Order.h"

Order::Order(const Order& o)
{
	this->_ID = o._ID;
	this->_SellerID = o._SellerID;
	this->_BuyerID = o._BuyerID;
	this->_ShipperID = o._ShipperID;
	this->_PriceCoeff = o._PriceCoeff;
	this->_OrderDate = o._OrderDate;
	this->_ShippingDate = o._ShippingDate;
	this->_Status= o._Status;
	this->_Note = o._Note;
}

string Order::Status_String()
{
	switch (this->Status())
	{
		case BUYER_CANCELLED:
			return "Cancelled by buyer";
		case SELLER_CANCELLED:
			return "Cancelled by seller";
		case SELLER_PENDING:
			return "Waiting for seller approval";
		case SHIPPING_PENDING:
			return "Delivering";
		case COMPLETED:
			return "Completed";
		default:
			return "Unknown status";
	}
}

int64_t Order::TotalPrice()
{
	ProductProvider& _ProductProvider = ProductProvider::GetInstance();
	return _PriceCoeff * _ProductProvider.GetByID(_ProductID)->Price() + _ShippingFee;
}

void Order::GetInfo()
{
	cout << "ID            : " << this->ID() << endl;
	cout << "Product       : " << endl;
	cout << "Seller        : " << endl;
	cout << "Buyer         : " << endl;
	cout << "Shipper       : " << endl;
	cout << "Shipping fee  : " << this->ShippingFee() << endl;
	cout << "Total price   : " << this->TotalPrice() << endl;
	cout << "Ordered date  : " << this->OrderDate().Year << "-" << this->OrderDate().Month << "-" << this->OrderDate().Day << endl;
	cout << "Shipping date : " << this->ShippingDate().Year << "-" << this->ShippingDate().Month << "-" << this->ShippingDate().Day << endl;
	cout << "Status        : " << this->Status_String() << endl;
	cout << "Note          : " << (this->Note().length() == 0 ? "n/a" : this->Note()) << endl;
}
