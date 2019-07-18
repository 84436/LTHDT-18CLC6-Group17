#pragma once
#include "../_INCLUDES_.h"
#include "../Account/AccountProvider.h"
#include "../Account/Seller.h"
#include "ProductProvider.h"

class Product {
	private:
		AccountProvider* _AccountProvider = nullptr;
		string _SellerID;
		string _ID;
		bool _isR18 = false;
		string _Name;
		string _Category;
		string _Decription;
		int32_t _Stock = 0;
		int64_t _Price = 0;
		vector<int> _Rating = {0};

	public:
		Product() {}
		Product(AccountProvider* _AccountProvider);
		Product(const Product& p);

		string  SellerID		()							{ return this->_SellerID; }
		void	SellerID		(string _SellerID)			{ this->_SellerID = _SellerID; }
		string  ID				()							{ return this->_ID; }
		void    ID				(string ID)					{ this->_ID = ID; }
		bool	isR18			()							{ return this->_isR18; }
		void	isR18			(bool _isR18)				{ this->_isR18 = _isR18; }
		string  Name			()							{ return this->_Name; }
		void    Name			(string Name)				{ this->_Name = Name; }
		string  Category		()							{ return this->_Category; }
		void    Category		(string Category)			{ this->_Category = Category; }
		string  Description		()							{ return this->_Category; }
		void    Description		(string Description)		{ this->_Decription = Description; }
		int32_t Stock			()							{ return this->_Stock; }
		void    Stock			(int32_t Stock)				{ this->_Stock = Stock; }
		int64_t Price			()							{ return this->_Price; }
		void    Price			(int64_t Price)				{ this->_Price = Price; }

		// void GetInfo();
		void Rate(int);
};
