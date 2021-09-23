#include "Bank.h"

std::shared_ptr<Bank> Bank::instanceOfBank = 0;
int main()
{
	std::shared_ptr<Bank> myBank = myBank->GetInstanceOfBank();

	myBank->mainMenu();
}