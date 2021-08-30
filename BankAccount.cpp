#include "BankAccount.h"

////// CONSTRUCTOR(S)

BankAccount::BankAccount(std::string sAccountName, std::string sAccountSurname, std::string sAccountIban)
{
	sName = sAccountName;
	sSurname = sAccountSurname;
	sIban = sAccountIban;
}

BankAccount::BankAccount(std::string sAccountName, std::string sAccountSurname, CURRENCY eAccountCurrency, std::string sAccountIban, double fAccountBalance)
{
	sName = sAccountName;
	sSurname = sAccountSurname;
	eCurrency = eAccountCurrency;
	sIban = sAccountIban;
	fBalance = fAccountBalance;
}

////// DESTRUCTOR

BankAccount::~BankAccount() {}

////// GETTER(S)

std::string BankAccount::sGetName() const { return sName; }
std::string BankAccount::sGetSurname() const { return sSurname; }
CURRENCY BankAccount::eGetCurrency() const { return eCurrency; }
std::string BankAccount::sGetIban() const { return sIban; }
double BankAccount::fGetBalance() const { return fBalance; }
std::string BankAccount::sGetCurrencyAsString()
{
	switch (eGetCurrency())
	{
	case CURRENCY::RON:
		return "RON";
	case CURRENCY::DOLLAR:
		return "DOLLAR";
	case CURRENCY::EURO:
		return "EURO";
	default:
		return "INVALID";
	}
}

////// SETTER(S)

void BankAccount::sSetName(std::string sAccountName) { sName = sAccountName; }
void BankAccount::sSetSurname(std::string sAccountSurname) { sSurname = sAccountSurname; }
void BankAccount::eSetCurrency(CURRENCY eAccountCurrency) { eCurrency = eAccountCurrency; }
void BankAccount::sSetIban(std::string sAccountIban) { sIban = sAccountIban; }
void BankAccount::fSetBalance(double fAccountBalance) { fBalance = fAccountBalance; }
void BankAccount::SetCurrencyFromIban()
{
	std::string sCurrentAccountIban = sGetIban();
	std::string sCurrencySubstring = sCurrentAccountIban.substr(sCurrentAccountIban.find("ITBK") + 4, 4);

	for (auto iter = sCurrencySubstring.begin(); iter != sCurrencySubstring.end(); iter++)
		if (std::isdigit(*iter))
		{
			eSetCurrency(CURRENCY::RON);
			break;
		}

	if (sCurrencySubstring == "EEUR")
		eSetCurrency(CURRENCY::EURO);
	else if (sCurrencySubstring == "EUSD")
		eSetCurrency(CURRENCY::DOLLAR);
}

////// UTILITIES
bool bank_utilities::IsValidNameOrSurname(std::string sName)
{
	if (sName.empty() || sName.length() > 12)
		return false;

	for (int i = 0; i < sName.length(); i++)
		if (!std::isalpha(sName.at(i)))
			if (!std::isspace(sName.at(i)))
				if (sName.at(i) != '-')
					return false;


	return true;
}

bool bank_utilities::IsValidBalance(std::string sBalance)
{
	if (sBalance.empty() || sBalance.length() > 14)
		return false;

	for (int i = 0; i < sBalance.length(); i++)
		if (!std::isdigit(sBalance.at(i)))
			if (sBalance.at(i) != '.')
			return false;

	return true;
}
