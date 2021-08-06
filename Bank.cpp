#include "Bank.h"

Bank::Bank()
{

}

Bank::~Bank()
{
	vBankAccounts.clear();
}

void Bank::vAddAccount()
{
	std::cout << "Introduceti prenumele utilizatorului: ";
	std::string sName;
	std::cin >> sName;

	std::cout << "Introduceti numele utlizatorului: ";
	std::string sSurname;
	std::cin >> sSurname;

	std::string sIban{ createIban() };

	BankAccount* account = new BankAccount(sName, sSurname, sIban);
	vBankAccounts.push_back(account);
}

std::string Bank::createIban()
{

	return std::string();
}
