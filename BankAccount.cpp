#include "BankAccount.h"

////// CONSTRUCTORS

BankAccount::BankAccount(std::string sAccountName, std::string sAccountSurname, std::string sAccountIban)
{
	this->sName = sAccountName;
	this->sSurname = sAccountSurname;
	this->sIban = sAccountIban;
}

////// DESTRUCTOR

BankAccount::~BankAccount() {}

////// GETTERS

inline std::string BankAccount::sGetName() const { return sName; }
inline std::string BankAccount::sGetSurname() const { return sSurname; }
inline CURRENCY BankAccount::eGetCurrency() const { return eCurrency; }
inline std::string BankAccount::sGetIban() const { return sIban; }
inline double BankAccount::fGetBalance() const { return fBalance; }

////// SETTERS

void BankAccount::sSetName(std::string sAccountName) { sName = sAccountName; }
void BankAccount::sSetSurname(std::string sAccountSurname) { sSurname = sAccountSurname; }
void BankAccount::eSetCurrency(CURRENCY eAccountCurrency) { eCurrency = eAccountCurrency; }
void BankAccount::sSetIban(std::string sAccountIban) { sIban = sAccountIban; }
void BankAccount::fSetBalance(double fAccountBalance) { fBalance = fAccountBalance; }