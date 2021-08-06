#pragma once

#include "BankAccount.h"

#include <vector>
#include <cstdio>

class Bank
{
public:
	Bank();
	~Bank();
	void vAddAccount();


private:
	std::vector<BankAccount*> vBankAccounts;
	std::string createIban();

};