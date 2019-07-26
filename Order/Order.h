#pragma once
#include "../_INCLUDES_.h"
#include "..///Product/ProductProvider.h"

// Statuses
auto constexpr BUYER_PENDING = 1;
auto constexpr BUYER_CANCELLED = -1;
auto constexpr SELLER_PENDING = 2;
auto constexpr SELLER_CANCELLED = -2;
auto constexpr SHIPPING_PENDING = 3;
auto constexpr COMPLETED = 0;

struct Date {
	int8_t Day;
	int8_t Month;
	int16_t Year;
	
	static Date Today()
	{
		Date x;
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);
		x.Year = newtime.tm_year + 1900;
		x.Month = newtime.tm_mon + 1;
		x.Day = newtime.tm_mday;
		return x;
	}

	static string Month_String(int _Month)
	{
		switch (_Month)
		{
			case 1:  return "Janunary";
			case 2:  return "February";
			case 3:  return "March";
			case 4:  return "April";
			case 5:  return "May";
			case 6:  return "June";
			case 7:  return "July";
			case 8:  return "August";
			case 9:  return "September";
			case 10: return "October";
			case 11: return "November";
			case 12: return "December";
			default: return "";
		}
	}
};

class Order {
	private:
		string _ID;
		string _ProductID;
		string _SellerID;
		string _BuyerID;
		string _ShipperID;
		double _PriceCoeff = 1;
		int64_t _ShippingFee = 0;
		Date _OrderDate = { 1,1,1 };
		Date _ShippingDate = { 1,1,1 };
		int8_t _Status = 0;
		string _Note;
		int32_t _Quantity = 0;

	public:
		Order() {}
		Order(const Order& _Order);

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
		int32_t Quantity		()						{ return this->_Quantity; }
		void	Quantity		(int32_t _Quantity)		{ this->_Quantity = _Quantity; }
		
		string Status_String();

		int64_t TotalPrice();
		void GetInfo();
};
