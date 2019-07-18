#include "Wallet.h"

Wallet::Wallet() {}

Wallet::Wallet(int64_t _Balance)
{
	this->_Balance = _Balance;
}

void Wallet::Balance(int64_t _Balance)
{
	this->_Balance = _Balance;
}

int64_t Wallet::Balance() const
{
	return this->_Balance;
}

void Wallet::Deposit(int64_t x)
{
	if (x >= 0) _Balance += x;
}

void Wallet::Withdraw(int64_t x)
{
	if (_Balance >= x) _Balance -= x;
}
