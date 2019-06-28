#include <iostream>
using namespace std;

class Wallet {
private:
	uint64_t Balance;
public:
	Wallet(uint64_t);
	uint64_t CheckWallet();
	void Deposit(uint64_t);
	void Withdraw(uint64_t);
};