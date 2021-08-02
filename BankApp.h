#pragma once
#include <iostream>
#include <string>

enum class CURRENCY
{
	UNKNOWN,
	EURO,
	DOLLAR,
	RON
};

class BankAccount
{
public:

	////// CONSTRUCTORS
	BankAccount(std::string sAccountName, std::string sAccountSurname, std::string sAccountIban);

	////// GETTERS
	std::string sGetName();
	std::string sGetSurname();
	CURRENCY eGetCurrency();
	std::string sGetIban();
	double fGetBalance();

	////// SETTERS
	void sSetName(std::string sAccountName);
	void sSetSurname(std::string sAccountSurname);
	void eSetCurrency(CURRENCY eAccountCurrency);
	void sSetIban(std::string sAccountIban);
	void fSetBalance(double fAccountBalance);

private:
	std::string sName = "Undefined";
	std::string sSurname = "Undefined";
	CURRENCY eCurrency = CURRENCY::UNKNOWN;
	std::string sIban = "Undefined";
	double fBalance = 0;
};