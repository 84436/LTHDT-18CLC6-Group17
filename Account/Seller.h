#pragma once
#include "../_INCLUDES_.h"
#include "Account.h"

class Seller : public Account
{
	private:
		struct ProductStatItem
		{
			string ProductID;
			int32_t Quantity = 0;
			int64_t TotalTotalPrice = 0;
		};
		vector<int16_t> _Rating = { 0, 0, 0, 0, 0 };

	public:
		Seller() : Account() {}
		Seller(const Seller& s) : Account(s) { this->_Rating = s._Rating; }

		void GetInfo();

		void ListOrder_Pending();
		void AcceptOrder(string _OrderID); 
		void RejectOrder(string _OrderID); 

		void ShowCategories();
		void ListProduct();
		void GetProductByID(string _ProductID);
		void AddProduct();
		void EditProduct(string _ProductID);
		void AddStock(string _ProductID, int32_t _Amount);
		void ClearStock(string _ProductID);

		void ListShippers();

		vector<int16_t> RatingArray();
		void RatingArray(int16_t _1, int16_t _2, int16_t _3, int16_t _4, int16_t _5);

		void Rate(int _score);
		float GetRate();

		// Statistics
		void StatsByMonth(int16_t _Year, int8_t _Month);
};
