#pragma once
#include "../_INCLUDES_.h"

struct Date {
	int Day;
	int Month;
	int Year;
};

class Order {
private:
	string _ID;
	Product* _Product;
	Seller* _Seller;
	Buyer* _Buyer;
	Shipper* _Shipper;
	float _PriceCoeff = 0;
	Date _OrderDate = { 1,1,1 };
	Date _ShippingDate = { 1,1,1 };
	uint8_t _Status = 0;
	string _Note;
	AccountProvider* _AccountProvider;
	ProductProvider* _ProductProvider;

public:
	Order();
	Order(AccountProvider* _AccountProvider, ProductProvider* _ProductProvider);
	Order(const Order& o);

	string  ID() { return this->_ID; }
	void    ID(string ID) { this->_ID = ID; }
	string  ProductID() { return this->_Product->ID(); }
	void	ProductID(string ProductID) { this->_Product = _ProductProvider->GetByID(ProductID); }
	string  SellerID() { return this->_Seller->ID(); }
	void	SellerID(string SellerID) { this->_Seller = _AccountProvider->FindSeller(SellerID); }
	string  BuyerID() { return this->_Buyer->ID(); }
	void	BuyerID(string BuyerID) { this->_Buyer = _AccountProvider->FindBuyer(BuyerID); }
	string  ShipperID() { return this->_Shipper->ID(); }
	void	ShipperID(string ShipperID) { this->_Shipper = _AccountProvider->FindShipper(ShipperID); }
	float   PriceCoeff() { return this->_PriceCoeff; }
	void    PriceCoeff(float PriceCoeff) { this->_PriceCoeff = PriceCoeff; }
	Date    OrderDate() { return this->_OrderDate; }
	void    OrderDate(Date OrderDate) { this->_OrderDate = OrderDate; }
	Date    ShippingDate() { return this->_ShippingDate; }
	void    ShippingDate(Date ShippingDate) { this->_ShippingDate = ShippingDate; }
	uint8_t Status() { return this->_Status; }
	void    Status(uint8_t Status) { this->_Status = Status; }
	string  Note() { return this->_Note; }
	void    Note(string Note) { this->_Note = Note; }

	int64_t getTotalPrice();
	uint8_t getStatus();
};
