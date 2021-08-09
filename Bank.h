#pragma once

#include "BankAccount.h"

#include <vector>
#include <cstdio>
#include <cstdlib>

class Bank
{
public:
	Bank();
	~Bank();

	std::vector<BankAccount*> vGetBankAccounts() { return vBankAccounts; }

private:
	std::vector<BankAccount*> vBankAccounts;
	std::string createIban(CURRENCY userCurrency);
	void vAddAccount();
	void vSeeAccounts() const;
	void mainMenu();
	void vModifyAccount();
};