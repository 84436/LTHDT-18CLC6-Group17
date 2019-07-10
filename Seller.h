#include "Person.h"

class Seller : public Person {
private:
	int Rating[5];
	vector <Shipper> Shippers;
public:
	void ListProduct();
	void CreateProduct();
	void EditProduct(Product);
};