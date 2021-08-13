#include "Bank.h"

int main()
{
	UserAccount* admin = new UserAccount();
	Bank* itSchoolBank = nullptr;
	UserAccount* user = nullptr; 
	int iLoginAttempts = 4;

	while (true)
	{
		if (iLoginAttempts == 0)
		{
			system("cls");
			std::cout << "AUTENTIFICARE ESUATA! APLICATIA SE VA OPRI...\n\n";
			return 0;
		}

		std::string sName, sPassword;
		std::cout << "Introduceti numele utilizatorului: ";
		std::getline(std::cin, sName);

		std::cout << "Introduceti parola utilizatorului: ";
		std::getline(std::cin, sPassword);

		user = new UserAccount(sName, sPassword);
		if (user->bDoesAccountHaveAccess(admin))
		{
			delete user;
			itSchoolBank = new Bank();
			break;
		}
		else
		{
			std::cout << "Mai aveti " << --iLoginAttempts << " incercari.\n";
		}
	}

	itSchoolBank->mainMenu();

	if (itSchoolBank != nullptr)
		delete itSchoolBank;

	if (user != nullptr)
		delete user;

	delete admin;
}