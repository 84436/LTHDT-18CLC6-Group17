#pragma once
#include "../_INCLUDES_.h"
#include "../Provider/Provider.h"
#include "../Account/AccountProvider.h"
#include "../Product/Product.h"

class ProductProvider : public Provider
{
	private:
		list<Product> Products;
		AccountProvider* _AccountProvider;

	public:
		void SetAccountProvider(AccountProvider* _AccountProvider);

		void ReadFile();
		void WriteFile();
		void Add(Product _Product);
		void Delete(string _ID);
		Product* GetByID(string _ID);
		list<Product> SearchByName(string _Name);
		list<Product> SearchBySeller(string _SellerID);
};
