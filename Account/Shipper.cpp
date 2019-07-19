#include "Shipper.h"
#include "../Product/Product.h"
#include "../Order/OrderProvider.h"

void Shipper::FinishOrder(string _OrderID)
{
	Order* o = OrderProvider::GetInstance().GetByID(_OrderID);
	if (o == nullptr)
	{
		cout << "Order " << _OrderID << " does not exist." << endl;
	}
	if (o->Status() != SHIPPING_PENDING)
	{
		cout << "This order was already completed." << endl;
	}
	o->Status(COMPLETED);

	AccountProvider::GetInstance().FindBuyer(o->BuyerID())->Withdraw(o->TotalPrice());

	AccountProvider::GetInstance().FindSeller(o->SellerID())->Deposit(o->TotalPrice() - o->ShippingFee());

	AccountProvider::GetInstance().FindShipper(this->ID())->Deposit(o->ShippingFee());
}
