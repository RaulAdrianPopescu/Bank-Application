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

	////// DESTRUCTOR
	~BankAccount();

	////// GETTERS
	inline std::string sGetName() const;
	inline std::string sGetSurname() const;
	inline CURRENCY eGetCurrency() const;
	inline std::string sGetIban() const;
	inline double fGetBalance() const;

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