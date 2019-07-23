#pragma once
#include "../_INCLUDES_.h"
#include "../Product/Product.h"

class ProductProvider
{
	private:
		ProductProvider();
		~ProductProvider() {}
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
		list<Product> ListBySellerID(string _SellerID, bool _isR18);
		list<Product> Search(string _Query, bool _isR18);
};
