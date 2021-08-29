#pragma once

#include "STL.h"

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

	////// CONSTRUCTOR(S)
	BankAccount(std::string sAccountName, std::string sAccountSurname, std::string sAccountIban);
	BankAccount(std::string sAccountName, std::string sAccountSurname, CURRENCY eAccountCurrency, std::string sAccountIban, double fAccountBalance);

	////// DESTRUCTOR
	~BankAccount();

	////// GETTER(S)
	std::string sGetName() const;
	std::string sGetSurname() const;
	CURRENCY eGetCurrency() const;
	std::string sGetIban() const;
	double fGetBalance() const;
	std::string sGetCurrencyAsString();

	////// SETTER(S)
	void sSetName(std::string sAccountName);
	void sSetSurname(std::string sAccountSurname);
	void eSetCurrency(CURRENCY eAccountCurrency);
	void sSetIban(std::string sAccountIban);
	void fSetBalance(double fAccountBalance);
	void SetCurrencyFromIban();

private:

	////// FIELD(S)
	std::string sName = "Undefined";
	std::string sSurname = "Undefined";
	CURRENCY eCurrency = CURRENCY::UNKNOWN;
	std::string sIban = "Undefined";
	double fBalance = 0;
};

////// UTILITIES
namespace bank_utilities
{
	bool IsValidNameOrSurname(std::string sName);
	bool IsValidBalance(std::string sBalance);
	void ClearBankAccounts(std::vector<std::pair<int, BankAccount*>> entries);
	void ClearBankAccounts(BankAccount* entry);
}