#include "Person.h"

class Buyer : public Person {
private:
	
public:
	Buyer() :Person() {};
	void SearchProduct();
	Order CreateOrder();
	void CancelOrder(Order& _order);
	void Rate(Order& _order);
};