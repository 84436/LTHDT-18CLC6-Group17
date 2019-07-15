#include "Order.h"

void Order::SetPriceCoeff(float _coeff){
	PriceCoeff = _coeff;
}

int64_t Order::getTotalPrice()
{
	return PriceCoeff * Product->getPrice() + Product->getShippingFee();
}

uint8_t Order::getStatus()
{
	if (Status == 1) {
		cout << "Your Order is Being Prepared " << endl;
	}
	else if (Status == 2) {
		cout << "Your Order is Delivering " << endl;
	}
	else if (Status == 3) {
		cout << "Your Order has Arrived !!! " << endl;
	}
	else if (Status == 0) {
		cout << "Your Order has been Cancelled !!! " << endl;
	}
	return Status;
}

string Order::getNote()
{
	return Note;
}

void Order::setStatus(uint8_t _status){
	Status = _status;
}

void Order::setNote(string _note){
	Note = _note;
}

