#include "Bank.h"

Bank::Bank()
{
    this->mainMenu();
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

    std::cout << "\n1 -> Pentru a mai adauga un cont\n";
    std::cout << "2 -> Pentru a reveni in meniul principal\n";
    int iOption = 0;
    std::cin >> iOption;
    
    switch (iOption)
    {
    case 1:
        system("CLS");
        vAddAccount();
        break;
    default: 
        break;
    }
}

void Bank::vSeeAccounts() const
{
	std::cout << "Numarul de conturi din baza de data a bancii este: " << vBankAccounts.size();
	std::cout << "\n\n";

    if (!vBankAccounts.empty())
    {
        for (int i = 0; i < vBankAccounts.size(); i++)
        {
            std::cout << "Contul " << i + 1 << ": " << vBankAccounts[i]->sGetName()
                      << ' ' << vBankAccounts[i]->sGetSurname()
                      << "       " << vBankAccounts[i]->sGetIban() << '\n';
        }
    }
    else { std::cout << "NU A FOST INREGISTRAT NICIUN CONT IN BAZA DE DATE!\n"; }
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
