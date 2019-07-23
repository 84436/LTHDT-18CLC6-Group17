#include "Shipper.h"
#include "../Product/Product.h"
#include "../Order/OrderProvider.h"

void Shipper::ListOrder_Pending()
{
	list<Order> FilteredOrders = OrderProvider::GetInstance().ListByAccountID(this->ID());

	FilteredOrders.remove_if(OrderProvider::isNotShipperPending);

	cout << "Total pending order count: " << FilteredOrders.size() << endl;
	for (auto i = FilteredOrders.begin(); i != FilteredOrders.end(); ++i)
	{
		cout << (*i).ID() << " : " << (*i).Status_String() << endl;
	}
}

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

	o->ShippingDate(Date::Today());

	AccountProvider::GetInstance().GetBuyer(o->BuyerID())->Withdraw(o->TotalPrice());

	AccountProvider::GetInstance().GetSeller(o->SellerID())->Deposit(o->TotalPrice() - o->ShippingFee());

	AccountProvider::GetInstance().GetShipper(this->ID())->Deposit(o->ShippingFee());
}

void Shipper::StatsByMonth(uint8_t _Month)
{
	if (_Month < 1 || _Month > 12)
	{
		cout << "Invalid month" << endl;
		return;
	}

	list<Order> FilteredOrders = OrderProvider::GetInstance().ListByAccountID(this->ID());
	for (auto i = FilteredOrders.begin(); i != FilteredOrders.end(); ++i)
	{
		if ((*i).ShippingDate().Month != _Month) FilteredOrders.erase(i);
	}

	// What month is it?

	// Total $
	int64_t Total = 0;
	for (auto i = FilteredOrders.begin(); i != FilteredOrders.end(); ++i)
	{
		Total += (*i).ShippingFee();
	}
	cout << "Total income = " << Total << endl;
}
