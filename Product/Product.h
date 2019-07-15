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
		int Rating[5] = {0};

	public:
		Product(string SellerID, string _ID, string Name, string Category, string Description, int32_t Stock, int64_t Price, int64_t ShippingFee);
		Product(const Product& p);

		// Getters + Setters.
		// string GetSellerID() { return this-Seller.GetID(); }
		void	SetSellerID(string SellerID)		 { }
		string  ID()							 { return this->_ID; }
		void    ID(string ID)					 { this->_ID = ID; }
		string  Name()							 { return this->_Name; }
		void    Name(string Name)				 { }
		string  Category()						 { }
		void    Category(string Category)		 { }
		string  Description()					 { }
		void    Description(string Description)  { }
		int32_t Stock()							 { }
		void    Stock(int32_t Stock)			 { }
		int64_t Price()							 { }
		void    Price(int64_t Price)			 { }
		int64_t ShippingFee()					 { }
		void    ShippingFee(int64_t ShippingFee) { }

		void GetInfo();
		void Rate(int);
};
