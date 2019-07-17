#pragma once
#include "../_INCLUDES_.h"

class Product {
	protected:
		Seller* _Seller;
		string _ID;
		string _Name;
		string _Category;
		string _Decription;
		int32_t _Stock = 0;
		int64_t _Price = 0;
		int64_t _ShippingFee = 0;
		int _Rating[5] = {0};
		AccountProvider* _AccountProvider; //TODO

	public:
		Product();
		Product(AccountProvider* _AccountProvider, string _SellerID, string _ID, string _Name, string _Category, string _Description, int32_t _Stock, int64_t _Price, int64_t _ShippingFee);
		Product(const Product& p);

		// Getters + Setters.
		string  SellerID()						 { return this->_Seller->ID(); }
		void	Seller(string SellerID)			 { _Seller = _AccountProvider->findSeller(SellerID); }
		string  ID()							 { return this->_ID; }
		void    ID(string ID)					 { this->_ID = ID; }
		string  Name()							 { return this->_Name; }
		void    Name(string Name)				 { this->_Name = Name; }
		string  Category()						 { return this->_Category; }
		void    Category(string Category)		 { this->_Category = Category; }
		string  Description()					 { return this->_Category; }
		void    Description(string Description)  { this->_Decription = Description; }
		int32_t Stock()							 { return this->_Stock; }
		void    Stock(int32_t Stock)			 { this->_Stock = Stock; }
		int64_t Price()							 { return this->_Price; }
		void    Price(int64_t Price)			 { this->_Price = Price; }
		int64_t ShippingFee()					 { return this->_ShippingFee; }
		void    ShippingFee(int64_t ShippingFee) { this->_ShippingFee = ShippingFee; }

		void GetInfo();
		void Rate(int);
};
