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
		Buyer * _Buyer;
		Shipper* _Shipper;
		float _PriceCoeff = 0;
		Date _OrderDate = { 1,1,1 };
		Date _ShippingDate = { 1,1,1 };
		uint8_t _Status = 0;
		string _Note;

	public:
		Order();
		Order(string _ID, string _ProductID, string _SellerID, string _BuyerID, string _ShipperID, float _PriceCoeff, Date _OrderDate, Date _ShippingDate, string _Note);
		Order(const Order& o);

		string  ID() { return this->_ID; }
		void    ID(string ID) { this->_ID = ID; }
		string  ProductID() { return this->_Product->ID(); }
		void	Product(string SellerID) { } //TO DO
		string  SellerID() { return this->_Seller->ID(); }
		void	Seller(string SellerID) { } //TO DO
		string  SellerID() { return this->_Seller->ID(); }
		void	setSeller(string SellerID) { } //TO DO
		string  Name() { return this->_Name; }
		void    Name(string Name) { this->_Name = Name; }
		string  Category() { return this->_Category; }
		void    Category(string Category) { this->_Category = Category; }
		string  Description() { return this->_Category; }
		void    Description(string Description) { this->_Decription = Description; }
		int32_t Stock() { return this->_Stock; }
		void    Stock(int32_t Stock) { this->_Stock = Stock; }
		int64_t Price() { return this->_Price; }
		void    Price(int64_t Price) { this->_Price = Price; }
		int64_t ShippingFee() { return this->_ShippingFee; }
		void    ShippingFee(int64_t ShippingFee) { this->_ShippingFee = ShippingFee; }

		void SetPriceCoeff(float _coeff);
		int64_t getTotalPrice();
		uint8_t getStatus();
		string getNote();
		void setStatus(uint8_t);
		void setNote(string);
};
