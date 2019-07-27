#pragma once
#include "../_INCLUDES_.h"

class Shell
{
	// Singleton
	private:
		Shell();
		~Shell();
	public:
		static Shell& GetInstance();

	// Shell itself
	private:
		string _AccountID;
		bool ShowLoginGreeter = true;

		// Command list: string-to-enum mapper
		enum class c;
		map<string, c> cMapper;
		void cMapper_Init();

		void Interpret(string _Command);

		// Native: Login
		void LoginGreeter();
		void CommandGreeter();
		void NewAccount(char AccountType);
		void LogIn();
		void ChangePassword();
		void ShowHelp();

		// Callbacks: Account
		void ShowInfo();
		void EditInfo();
		void WalletCheck();
		void WalletWithdraw();
		void WalletTopUp();

		// Callbacks: Order
		void ListOrder();
		void ListPendingOrder();
		void LookupOrder();
		void CreateOrder();
		void AcceptOrder();
		void RejectOrder();
		void RateOrder();

		// Callbacks: Product
		void ListProduct();
		void LookupProduct();
		void SearchProduct();
		void ListProductBySeller();
		void AddProduct();
		void EditProduct();
		void DeleteProduct();
		void AddStock();

		// Callbacks: Shippers/Stats
		void ListShippers();
		void Ship();
		void Stats();

	public:
		void Loop();
};
