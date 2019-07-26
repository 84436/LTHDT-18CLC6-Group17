#include "Shipper.h"
#include "../Product/Product.h"
#include "../Order/OrderProvider.h"

void Shipper::ListOrder_Pending()
{
	list<Order> FilteredOrders = OrderProvider::GetInstance().ListByAccountID(this->ID());

	FilteredOrders.remove_if(OrderProvider::isNotPending_Shipper);

	cout << "Total pending order count: " << FilteredOrders.size() << endl;
	for (auto i = FilteredOrders.begin(); i != FilteredOrders.end(); ++i)
	{
		cout << (*i).ID() << " : " << (*i).Status_String() << endl;
	}
}

void Shipper::FinishOrder(string _OrderID)
{
	if (!OrderProvider::isRelated(this->ID(), _OrderID))
	{
		cout << "Order not found." << endl;
		return;
	}

	Order* _Order = OrderProvider::GetInstance().GetByID(_OrderID);
	
	if (_Order->Status() != SHIPPING_PENDING)
	{
		cout << "This order was already completed." << endl;
	}
	_Order->Status(COMPLETED);

	_Order->ShippingDate(Date::Today());

	AccountProvider::GetInstance().GetBuyer(_Order->BuyerID())->Withdraw(_Order->TotalPrice());

	AccountProvider::GetInstance().GetSeller(_Order->SellerID())->Deposit(_Order->TotalPrice() - _Order->ShippingFee());

	AccountProvider::GetInstance().GetShipper(this->ID())->Deposit(_Order->ShippingFee());
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
