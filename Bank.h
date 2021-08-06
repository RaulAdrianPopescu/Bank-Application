#pragma once

#include "BankAccount.h"

#include <vector>
#include <cstdio>

class Bank
{
public:
	Bank();
	~Bank();

private:
	std::vector<BankAccount*> vBankAccounts;
	std::string createIban();
	void vAddAccount();
	void vSeeAccounts() const;
	void mainMenu();

};