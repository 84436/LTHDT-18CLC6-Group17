#include <iostream>
#include "Seller.h"
#include "Buyer.h"
#include "Shipper.h"
#include "Product.h"


using namespace std;

struct Date {
	int Day;
	int Month;
	int Year;
};

class Order {
private:
	string ID;
	Product* Product;
	Seller* Seller;
	Buyer * Buyer;
	Shipper* Shiper;
	float PriceCoeff;
	Date OrderDate;
	Date ShippingDate;
	uint8_t Status;
	string Note;
public:
	void SetPriceCoeff(float _coeff);
	uint64_t getTotalPrice();
	uint8_t getStatus();
	string getNote();
	void setStatus(uint8_t);
	void setNote(string);
};