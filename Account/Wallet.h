#pragma once
#include "../_INCLUDES_.h"

class Wallet {
	private:
		int64_t _Balance = 0;

	public:
		Wallet();
		Wallet(int64_t _Balance);
		void	Balance(int64_t _Balance);
		int64_t	Balance() const;
		void	Deposit(int64_t x);
		void	Withdraw(int64_t x);
};
