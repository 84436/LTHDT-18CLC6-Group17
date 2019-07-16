#pragma once
#include "../_INCLUDES_.h"

class Wallet {
	private:
		int64_t Balance;

	public:
		Wallet();
		Wallet(int64_t);
		void setBalance(int64_t);
		int64_t checkWallet();
		void Deposit(int64_t);
		void Withdraw(int64_t);
};
