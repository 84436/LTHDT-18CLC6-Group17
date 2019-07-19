#pragma once
#include "../_INCLUDES_.h"
#include "..///Product/ProductProvider.h"

// Statuses
auto constexpr BUYER_CANCELLED = 1;
auto constexpr SELLER_CANCELLED = 2;
auto constexpr SELLER_PENDING = 3;
auto constexpr SHIPPING_PENDING = 4;
auto constexpr COMPLETED = 0;

struct Date {
	int Day;
	int Month;
	int Year;
};

class Order {
	private:
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
		Order(const Order& o);

		string  ID				()						{ return this->_ID; }
		void    ID				(string _ID)			{ this->_ID = _ID; }
		string  ProductID		()						{ return this->_ProductID; }
		void	ProductID		(string _ProductID)		{ this->_ProductID = _ProductID; }
		string  SellerID		()						{ return this->_SellerID; }
		void	SellerID		(string _SellerID)		{ this->_SellerID = _SellerID; }
		string  BuyerID			()						{ return this->_BuyerID; }
		void	BuyerID			(string _BuyerID)		{ this->_BuyerID = _BuyerID; }
		string  ShipperID		()						{ return this->_ShipperID; }
		void	ShipperID		(string _ShipperID)		{ this->_ShipperID = _ShipperID; }
		double  PriceCoeff		()						{ return this->_PriceCoeff; }
		void    PriceCoeff		(float _PriceCoeff)		{ this->_PriceCoeff = _PriceCoeff; }
		int64_t ShippingFee		()						{ return this->_ShippingFee; }
		void	ShippingFee(int64_t _ShippingFee)		{ this->_ShippingFee = _ShippingFee; }
		Date    OrderDate		()						{ return this->_OrderDate; }
		void    OrderDate		(Date _OrderDate)		{ this->_OrderDate = _OrderDate; }
		Date    ShippingDate	()						{ return this->_ShippingDate; }
		void    ShippingDate	(Date _ShippingDate)	{ this->_ShippingDate = _ShippingDate; }
		int8_t  Status			()						{ return this->_Status; }
		void    Status			(int8_t _Status)		{ this->_Status = _Status; }
		string  Note			()						{ return this->_Note; }
		void    Note			(string _Note)			{ this->_Note = _Note; }

		string Status_String();

		int64_t TotalPrice();
		void GetInfo();
};
