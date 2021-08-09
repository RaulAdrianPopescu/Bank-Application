#include "Bank.h"

Bank::Bank()
{
    mainMenu();
}

Bank::~Bank()
{
	vBankAccounts.clear();
}

void Bank::vAddAccount()
{
	std::cout << "Introduceti prenumele utilizatorului: ";
	std::string sSurname;
	std::cin >> sSurname;

	std::cout << "Introduceti numele utlizatorului: ";
	std::string sName;
	std::cin >> sName;

	std::string sIban;

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
            std::cout << "Contul " << i + 1 << ": " << vBankAccounts[i]->sGetSurname()
                      << ' ' << vBankAccounts[i]->sGetName()
                      << " ~~~~~~~~~ " << vBankAccounts[i]->sGetIban() << '\n';
        }
    }
    else { std::cout << "NU A FOST INREGISTRAT NICIUN CONT IN BAZA DE DATE!\n"; }

    std::cout << "\n\nAPASATI ORICE TASTA PENTRU A VA INTOARCE IN MENIU...";
    system("pause > nul");
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
            vAddAccount();
            break;
        case 2:
            vSeeAccounts();
            break;
        case 3:
            vModifyAccount();
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

void Bank::vModifyAccount()
{
    system("CLS");
    std::cout << "Introduceti prenumele si numele contului pe care doriti sa il modificati: ";
    std::string sName, sSurname;
    std::cin >> sSurname; std::cin.ignore();
    std::cin >> sName;

    BankAccount* temp = nullptr;
    std::vector<BankAccount*>::iterator iter = vBankAccounts.begin();

    while (iter != vBankAccounts.end())
    {
        if ((*iter)->sGetName() == sName && (*iter)->sGetSurname() == sSurname)
        {
            temp = *iter;
            break;
        }

        iter++;
    }

    if (temp == nullptr)
    {
        std::cout << "\nContul nu a fost gasit\n\n";
        std::cout << "1 -> Creati un cont\n";
        std::cout << "2 -> Cautati alt cont\n";
        std::cout << "0 -> Intoarcere la meniul principal\n";
        std::cout << "\nIntroduceti optiunea: ";
        int iOption;
        std::cin >> iOption;
        switch (iOption)
        {
        case 1:
            system("CLS");
            vAddAccount();
            break;
        case 2:
            vModifyAccount();
            break;
        case 0:
            mainMenu();
            break;
        default:
            break;
        }
    }

    else
    {
        system("CLS");
        std::cout << "Ce operatie doresti sa efectuezi asupra contului?\n\n";
        std::cout << "1 -> Modifica nume\n";
        std::cout << "2 -> Modifica prenume\n";
        std::cout << "3 -> Modifica suma din cont\n";
        std::cout << "0 -> Intoarcete in meniul principal\n";
        std::cout << "\nIntroduceti optiunea: ";
        int iOption;
        std::cin >> iOption;
        system("CLS");

        switch (iOption)
        {
        case 1:
        {
            std::cout << "Introduceti noul nume al contului: ";
            std::string sNewAccName;
            std::cin >> sNewAccName;
            temp->sSetName(sNewAccName);
            std::cout << "\nNumele a fost modificat cu succes!";
            std::cout << "\n\nAPASATI ORICE TASTA PENTRU A VA INTOARCE IN MENIU...";
            system("pause > nul");
        }
            break;
        case 2:
        {
            std::cout << "Introduceti noul prenume al contului: ";
            std::string sNewAccSurname;
            std::cin >> sNewAccSurname;
            temp->sSetSurname(sNewAccSurname);
            std::cout << "\nPrenumele a fost modificat cu succes!";
            std::cout << "\n\nAPASATI ORICE TASTA PENTRU A VA INTOARCE IN MENIU...";
            system("pause > nul");
        }
            break;
        default:
            break;
        }
    }
}

std::string Bank::createIban(CURRENCY userCurrency)
{
    //std::string sIban[6] {"RO", "ITBK"};

    //switch (userCurrency)
    //{
    //case CURRENCY::RON:
    //    {
    //        srand()
    //    }
    //default:
    //    std::cout << "!!!Asigurativa ca acestui cont i-a fost atribuit o moneda. Codul IBAN nu a fost generat!!!\n";
    //    return NULL;
    //}
    return std::string();
    
}
