#pragma once
#include "../_INCLUDES_.h"

class Shell
{
	// Singleton
	private:
		Shell() {}
		~Shell() {}
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
		void NewAccount();
		void LogIn();
		void ChangePassword();
		void Greeter();
		void ShowHelp();
		void ShowInfo();

	public:
		void Loop();
};
