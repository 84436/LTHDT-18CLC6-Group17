#include "Wallet.h"

Wallet::Wallet(uint64_t x) {
	Balance = x;
}

uint64_t Wallet::CheckWallet() {
	return Balance;
}

void Wallet::Deposit(uint64_t x) {
	Balance += x;
}

void Wallet::Withdraw(uint64_t x) {
	if (Balance < x) {
		return;
	}
	Balance -= x;
}

