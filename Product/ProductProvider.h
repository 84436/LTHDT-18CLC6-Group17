#pragma once
#include "../_INCLUDES_.h"
#include "../Product/Product.h"
#include "../Account/AccountProvider.h"

class Product;

class ProductProvider
{
	private:
		ProductProvider();
	public:
		static ProductProvider& GetInstance();

	private:
		list<Product> Products;
		static int32_t NewProductIDCounter;
		string GenerateNewProductID();

	public:
		void ReadFile();
		void WriteFile();
		void Add(Product _Product);
		void Delete(string _ID);
		Product* GetByID(string _ID); 
		list<Product> SearchByName(string _Name, bool _isR18);
		list<Product> SearchBySeller(string _SellerID, bool _isR18);
};
