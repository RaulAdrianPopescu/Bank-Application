#pragma once

#include "STL.h"

class UserAccount
{
public:

	////// CONSTRUCTOR(S)
	UserAccount();												// Constructor-ul initializeaza un cont de utilizator doar daca este valid; verificati definitia din UserAccount.cpp pentru mai multe detalii legate de validare
	UserAccount(std::string sName, std::string sPassword);      // Constructor-ul initializeaza un cont de utilizator fara a mai fi nevoie de validare

	////// DESTRUCTOR
	~UserAccount();												// Destructor simplu

	////// GETTER(S)
	std::string const sGetUserName();							// Getter pentru numele utilizatorului
	std::string const sGetUserPassword();						// Getter pentru parola utilizatorului

	////// METHOD(S)
	bool bIsUserNameValid(std::string sInputName);			    // Metoda de tip bool prin care validam daca un nume de utilizator este valid sau nu; verificati UserAccount.cpp pentru detalii legate de validare
	bool bIsUserPasswordValid(std::string sInputPassword);		// Metoda de tip bool prin care validam daca o parola este valida sau nu; verificati UserAccount.cpp pentru detalii legate de validare

private:

	////// FIELD(S)
	void sSetUserName(std::string& sInputName);					// Setter pentru numele de utlizator
	void sSetUserPassword(std::string& sInputPassword);			// Setter pentru parola utlizatorului
	std::string sUserName;
	std::string sUserPassword;
};