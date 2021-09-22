#include "Bank.h"

std::unique_ptr<Bank> Bank::instanceOfBank = 0;
int main()
{
	std::unique_ptr<Bank> myBank = myBank->GetInstanceOfBank();

	myBank->mainMenu();
}