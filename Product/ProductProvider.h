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
		map<string, int64_t> ShippingFeeTable = { {"_INVALID CATEGORY_", 0} };
		string GenerateNewProductID();

	public:
		void ReadFile();
		void WriteFile();

		static bool isR18(Product _Product);
		static bool isRelated(string _SellerID, string _ProductID);

		void Add(Product _Product);
		void Delete(string _ID);
		Product* GetByID(string _ID); 
		list<Product> ListBySellerID(string _SellerID, bool _isR18);
		list<Product> ListByQuery(string _Query, bool _isR18);
		int64_t GetShippingFee(string _Category);
		list<string> Categories();
};
