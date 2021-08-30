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
	BankAccount(std::string sAccountName, std::string sAccountSurname, std::string sAccountIban);														// Constructor prin care creem un cont bancar in metoda AddAccount() din clasa Bank
	BankAccount(std::string sAccountName, std::string sAccountSurname, CURRENCY eAccountCurrency, std::string sAccountIban, double fAccountBalance);    // Constructor prin care initializam toate field-urile din cadrul unui cont bancar; necesar pentru metodele de vizualizare si modificare cont

	////// DESTRUCTOR
	~BankAccount();											// Destructor simplu

	////// GETTER(S)
	std::string sGetName() const;							// Getter prenume
	std::string sGetSurname() const;						// Getter nume
	CURRENCY eGetCurrency() const;							// Getter moneda
	std::string sGetIban() const;							// Getter IBAN
	double fGetBalance() const;								// Getter sold bancar
	std::string sGetCurrencyAsString();						// Getter moneda (conversie in string)

	////// SETTER(S)
	void sSetName(std::string sAccountName);				// Setter prenume
	void sSetSurname(std::string sAccountSurname);			// Setter nume
	void eSetCurrency(CURRENCY eAccountCurrency);			// Setter moneda
	void sSetIban(std::string sAccountIban);				// Setter IBAN
	void fSetBalance(double fAccountBalance);				// Setter sold
	void SetCurrencyFromIban();								// Setter prin care alegem moneda contului bazat pe al 3-lea sir de 4 caractere din IBAN

private:

	////// FIELD(S)
	std::string sName = "Undefined";
	std::string sSurname = "Undefined";
	CURRENCY eCurrency = CURRENCY::UNKNOWN;
	std::string sIban = "Undefined";
	double fBalance = 0;
};


/***********************************************************************************************
* Cateva functii de validare pentru soldul contului bancar si nume
* Aceste functii sunt de uz general si sunt incadrate doar intr-un namespace pentru easy of use
************************************************************************************************/
////// UTILITIES
namespace bank_utilities
{
	bool IsValidNameOrSurname(std::string sName);
	bool IsValidBalance(std::string sBalance);
}