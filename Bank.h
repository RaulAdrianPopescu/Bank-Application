#pragma once

#include "FileManager.h"

class Bank
{
public:

	////// DESTRUCTOR
	~Bank();											  // Default destructor

	////// METHOD(S)
	void mainMenu();									  // Metoda prin care accesam meniul principal al aplicatiei
	static std::shared_ptr<Bank> GetInstanceOfBank();     // Getter pentru pointer-ul din singleton

private:

	////// CONSTRUCTOR(S)
	Bank();								// Constructor-ul va deschide bazele de date de pe care operam si va servi drept meniu de login pentru aplicatie

	////// METHOD(S)
	CURRENCY eSelectCurrency();			// Metoda prin care selectam moneda in care va fi generat IBAN-ul
	void AddAccount();					// Metoda prin care putem adauga conturi bancare
	void SeeAccounts();					// Metoda ce va printa toate conturile bancare din baza de date, alaturi de numarul de inregistrare a fiecaruia
	void ModifyAccount();				// Metoda prin care putem modifica un cont bancar, in cazul in care sunt mai multe conturi sub acelasi nume, utilizatorul va primi un prompt cu numele, moneda si IBAN-ul contului iar apoi poate decide pe care vrea sa il modifice
	void AddUserAccount();				// Metoda prin care putem adauga un nou cont de utilizator in baza de date a utilizatorilor
	void DeleteUserAccount();           // Metoda prin care putem sterge alte conturi de utilizator din baza de date a utilizatorilor, dar nu si pe cel de pe care suntem logati in acest moment
	std::string sCreateIban();          // Metoda prin care generam un cod IBAN de 24 de caractere bazat pe moneda aleasa la creerea contului

	////// FIELD(S)
	std::unique_ptr<FileManagerBankAccounts> bankAccountDatabase;  // Un obiect ce ne permite manipularea bazei de date a conturilor bancare
	std::unique_ptr<FileManagerUserAccounts> userAccountDatabase;  // Un obiect ce ne permite manipularea bazei de date a conturilor de utilizatori
	std::shared_ptr<UserAccount> currentLogin;					   // Un obiect in care stocam contul de login la intrarea in aplicatie
	static std::shared_ptr<Bank> instanceOfBank;				   // Unique pointer ce reprezinta o singura instanta a bancii
};