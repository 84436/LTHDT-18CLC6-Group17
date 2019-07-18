#include "Order.h"

Order::Order()
{
	_ID = "";
	_Product = nullptr;
	_Seller = nullptr;
	_Buyer = nullptr;
	_Shipper = nullptr;
	_Note = "";
}

Order::Order(AccountProvider* _AccountProvider, ProductProvider* _ProductProvider)
{
	this->_AccountProvider = _AccountProvider;
	this->_ProductProvider = _ProductProvider;
}

Order::Order(const Order& o)
{
	this->_AccountProvider = _AccountProvider;
	this->_ProductProvider = _ProductProvider;
	this->_ID = o._ID;
	this->_Seller = o._Seller;
	this->_Buyer = o._Buyer;
	this->_Shipper = o._Shipper;
	this->_PriceCoeff = o._PriceCoeff;
	this->_OrderDate = o._OrderDate;
	this->_ShippingDate = o._ShippingDate;
	this->_Status= o._Status;
	this->_Note = o._Note;
}


int64_t Order::getTotalPrice()
{
	// return _PriceCoeff * _Product->Price() + _Product->ShippingFee();
	return _PriceCoeff * _Product->Price();
}

uint8_t Order::getStatus()
{
	if (_Status == 1) {
		cout << "Your Order is Being Prepared " << endl;
	}
	else if (_Status == 2) {
		cout << "Your Order is Delivering " << endl;
	}
	else if (_Status == 3) {
		cout << "Your Order has Arrived !!! " << endl;
	}
	else if (_Status == 0) {
		cout << "Your Order has been Cancelled !!! " << endl;
	}
	return _Status;
}

