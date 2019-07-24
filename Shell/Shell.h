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

		// Command list: string-to-enum mapper
		enum class c;
		map<string, c> cMapper;
		void cMapper_Init();

		void Interpret(string _Command);

		// Native: Login
		void NewAccount();
		void LogIn();
		void ChangePassword();
		void Greeter();
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

		// Callbacks: Product
		void ListProduct();
		void LookupProduct();
		void SearchProduct();
		void SearchProductBySeller();
		void AddProduct();
		void EditProduct();
		void DeleteProduct();
		void AddStock();

	public:
		void Loop();
};
