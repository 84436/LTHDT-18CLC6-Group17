#include "Person.h"
#include "Product.h"

class Shipper : public Person {
private:
	Product* Product;
public:
	Shipper() :Person() {};
	void setShippingFee(uint64_t x);
};