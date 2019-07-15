#include "Shipper.h"

void Shipper::setShippingFee(int64_t x){
	Product::setShippingFee(x);

}

void Shipper::updateStatus(uint8_t x){
	Order::setStatus(x);
}
