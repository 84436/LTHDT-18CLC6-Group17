#pragma once
#include "../_INCLUDES_.h"
#include "Account.h"

class Seller : public Account
{
	private:
		vector<int16_t> Rating = { 0, 0, 0, 0, 0 };

	public:
		Seller() : Account() {}
		Seller(const Seller& s) : Account(s) { this->Rating = s.Rating; }

		void GetInfo();

		void ListOrder_Pending();
		void AcceptOrder(string _OrderID); 
		void RejectOrder(string _OrderID); 

		void ListProduct();
		void GetProductByID(string _ProductID);
		void AddProduct();
		void EditProduct(string _ProductID);
		void DeleteProduct(string _ProductID);
		void AddStock(string _ProductID, int32_t _Amount);

		void ListShippers();

		vector<int16_t> RatingArray();
		void RatingArray(int16_t _1, int16_t _2, int16_t _3, int16_t _4, int16_t _5);

		void Rate(int _score);
		float GetRate();
		void CancelOrder(string _OrderID);

		// Statistics
		void StatsByMonth(uint8_t _Month);
		
};
