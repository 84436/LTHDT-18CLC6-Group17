#include "Wallet.h"

Wallet::Wallet() {
	Balance = 0;
}

Wallet::Wallet(int64_t x) {
	Balance = x;
}

void Wallet::setBalance(int64_t x){
	Balance = x;
}

int64_t Wallet::checkWallet() {
	return Balance;
}

void Wallet::Deposit(int64_t x) {
	Balance += x;
}

void Wallet::Withdraw(int64_t x) {
	if (Balance < x) {
		return;
	}
	Balance -= x;
}
