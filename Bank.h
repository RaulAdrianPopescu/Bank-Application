#pragma once

#include "FileManager.h"

class Bank
{
public:

	////// CONSTRUCTOR(S)
	Bank();

	////// DESTRUCTOR
	~Bank();

	////// METHOD(S)
	void mainMenu();
	static Bank* GetInstanceOfBank();

private:

	////// METHOD(S)
	CURRENCY eSelectCurrency();
	void AddAccount();
	void SeeAccounts();
	void ModifyAccount();
	void AddUserAccount();
	void DeleteUserAccount();
	std::string sCreateIban();

	////// FIELD(S)
	FileManagerBankAccounts* bankAccountDatabase;
	FileManagerUserAccounts* userAccountDatabase;
	UserAccount* currentLogin = nullptr;

	static Bank* instanceOfBank;
};