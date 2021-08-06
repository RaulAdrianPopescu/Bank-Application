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

void Bank::vSeeAccounts() const
{
	std::cout << "Numarul de conturi din baza de data a bancii este: " << vBankAccounts.size();
	std::cout << "\n\n";

	for (int i = 0; i < vBankAccounts.size(); i++)
	{
		std::cout << "Contul " << i + 1 << ": " << vBankAccounts[i]->sGetName()
			      << ' ' << vBankAccounts[i]->sGetSurname()
			      << "       " << vBankAccounts[i]->sGetIban() << '\n';
	}
}

void Bank::mainMenu()
{
    int iOption{ 10 }; // default value, so that we avoid undefined behaviour

    while (iOption)
    {
        system("CLS");
        std::cout << "Meniul Principal\n";

        std::cout << "1 -> Adaugare cont\n";
        std::cout << "2 -> Vizualizare conturi\n";
        std::cout << "3 -> Modificare conturi\n";
        std::cout << "0 -> Inchidere aplicatie.\n";
        std::cout << "Introduceti optiunea: ";
        std::cin >> iOption;
        system("CLS");


        switch (iOption)
        {
        case 1:
            this->vAddAccount();

            int addAccountOption{ 0 };

            break;
        case 2:
            this->vSeeAccounts();
            std::cout << "\n\nAPASATI ORICE TASTA PENTRU A VA INTOARCE IN MENIU...";
            system("pause > nul");
            break;
        case 0:
            std::cout << "La revedere...\n";
            break;
        default:
            std::cout << "Optiunea nu este valida.\n";
            break;
        }
    }
}

std::string Bank::createIban()
{

	return std::string();
}
