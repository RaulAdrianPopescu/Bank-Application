#pragma once

#include "BankAccount.h"

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>

class Bank
{
public:

	////// CONSTRUCTOR(S)
	Bank();

	////// DESTRUCTOR
	~Bank();

	////// GETTERS(S)
	std::vector<BankAccount*> vGetBankAccounts() { return vBankAccounts; }

	////// PUBLIC METHOD(S)
	void mainMenu();

private:

	////// PRIVATE METHOD(S)
	CURRENCY eSelectCurrency();
	void vAddAccount();
	void vSeeAccounts() const;
	void vModifyAccount();
	std::string sCreateIban();

	////// FIELD(S)
	std::vector<BankAccount*> vBankAccounts;
};

class UserAccount
{
public:

	////// CONSTRUCTOR(S)
	UserAccount();
	UserAccount(std::string sName, std::string sPassword);

	////// DESTRUCTOR
	~UserAccount();
	
	////// GETTER(S)
	std::string const sGetUserName();
	std::string const sGetUserPassword();

	////// METHOD(S)
	bool bIsUserNameValid(std::string sInputName);
	bool bIsUserPasswordValid(std::string sInputPassword);
	bool bDoesAccountHaveAccess(UserAccount* adminAccount);

private:

	////// FIELD(S)
	void sSetUserName(std::string& sInputName);
	void sSetUserPassword(std::string& sInputPassword);
	std::string sUserName;
	std::string sUserPassword;
};