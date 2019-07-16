#pragma once
#include "../_INCLUDES_.h"

class ProductProvider : public Provider
{
	private:
		list<Product> Products;

	public:
		void Add(Product _Product);
		void Delete(string _ID);
		Product* GetByID(string _ID);
		list<Product> Search(string _Name);
		list<Product> Search(Seller* _Seller);
};
