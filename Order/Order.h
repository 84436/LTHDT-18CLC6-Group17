#pragma once
#include "../_INCLUDES_.h"
#include "../Account/AccountProvider.h"
#include "../Product/ProductProvider.h"

struct Date {
	int Day;
	int Month;
	int Year;
};

class Order {
	private:
		AccountProvider* _AccountProvider = nullptr;
		ProductProvider* _ProductProvider = nullptr;
		string _ID;
		string _ProductID;
		string _SellerID;
		string _BuyerID;
		string _ShipperID;
		double _PriceCoeff = 0;
		int64_t _ShippingFee = 0;
		Date _OrderDate = { 1,1,1 };
		Date _ShippingDate = { 1,1,1 };
		int8_t _Status = 0;
		string _Note;

	public:
		Order() {}
		Order(AccountProvider* _AccountProvider, ProductProvider* _ProductProvider);
		Order(const Order& o);

		string  ID() { return this->_ID; }
		void    ID(string ID) { this->_ID = ID; }
		string  ProductID() { return this->_ProductID; }
		void	ProductID(string ProductID) { this->_ProductID = ProductID; }
		string  SellerID() { return this->_SellerID; }
		void	SellerID(string SellerID) { this->_SellerID = SellerID; }
		string  BuyerID() { return this->_BuyerID; }
		void	BuyerID(string BuyerID) { this->_BuyerID = BuyerID; }
		string  ShipperID() { return this->_ShipperID; }
		void	ShipperID(string ShipperID) { this->_ShipperID = ShipperID; }
		float   PriceCoeff() { return this->_PriceCoeff; }
		void    PriceCoeff(float PriceCoeff) { this->_PriceCoeff = PriceCoeff; }
		Date    OrderDate() { return this->_OrderDate; }
		void    OrderDate(Date OrderDate) { this->_OrderDate = OrderDate; }
		Date    ShippingDate() { return this->_ShippingDate; }
		void    ShippingDate(Date ShippingDate) { this->_ShippingDate = ShippingDate; }
		int8_t Status() { return this->_Status; }
		void    Status(int8_t Status) { this->_Status = Status; }
		string  Note() { return this->_Note; }
		void    Note(string Note) { this->_Note = Note; }

		int64_t getTotalPrice();
		int8_t getStatus();
};
