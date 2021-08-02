#include "BankApp.h"

////// CONSTRUCTORS

BankAccount::BankAccount(std::string sAccountName, std::string sAccountSurname, std::string sAccountIban)
{
	this->sName = sAccountName;
	this->sSurname = sAccountSurname;
	this->sIban = sAccountIban;
}

////// GETTERS

std::string BankAccount::sGetName() { return sName; }
std::string BankAccount::sGetSurname() { return sSurname; }
CURRENCY BankAccount::eGetCurrency() { return eCurrency; }
std::string BankAccount::sGetIban() { return sIban; }
double BankAccount::fGetBalance() { return fBalance; }

////// SETTERS

void BankAccount::sSetName(std::string sAccountName) { sName = sAccountName; }
void BankAccount::sSetSurname(std::string sAccountSurname) { sSurname = sAccountSurname; }
void BankAccount::eSetCurrency(CURRENCY eAccountCurrency) { eCurrency = eAccountCurrency; }
void BankAccount::sSetIban(std::string sAccountIban) { sIban = sAccountIban; }
void BankAccount::fSetBalance(double fAccountBalance) { fBalance = fAccountBalance; }
