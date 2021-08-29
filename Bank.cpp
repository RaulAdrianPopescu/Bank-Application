#include "Bank.h"

/////////////////  BANK \\\\\\\\\\\\\\\\\\

////// CONSTRUCTOR(S)
Bank::Bank() 
{
   bankAccountDatabase = new FileManagerBankAccounts("bank_accounts.csv");
   userAccountDatabase = new FileManagerUserAccounts("user_accounts.csv");

   if (!userAccountDatabase->HasUserAccounts())
   {
       std::cout << "Nu exista utilizatori in baza de data. Va rugam sa creati un cont.\n";
       
       std::cout << "\n\nAPASATI ORICE TASTA PENTRU A CONTINUA...";
       system("pause > nul");

       currentLogin = new UserAccount();
       userAccountDatabase->AddToFile(currentLogin);

       delete currentLogin;
   }
   else
   {
       int iLoginAttempts = 4;

       while (iLoginAttempts > 0)
       {
           system("cls");

           if (iLoginAttempts != 4)
               std::cout << "Informatiile introduse nu sunt corecte, te rugam sa reincerci. Incercari ramase: " << iLoginAttempts << "\n\n";

           if (currentLogin != nullptr)
               delete currentLogin;

           std::string sUserName, sUserPassword;
           std::cout << "Introduceti numele de utilizator: "; std::cin >> sUserName;
           std::cout << "Introduceti parola: "; std::cin >> sUserPassword;

           currentLogin = new UserAccount(sUserName, sUserPassword);
           if (!(currentLogin->bIsUserNameValid(currentLogin->sGetUserName())) || !(currentLogin->bIsUserPasswordValid(currentLogin->sGetUserPassword())))
               iLoginAttempts--;
           else if (!(userAccountDatabase->IsAccessAllowed(currentLogin)))
               iLoginAttempts--;
           else
               break;
       }

       if (iLoginAttempts == 0)
           std::exit(2);
   }
}

////// DESTRUCTOR
Bank::~Bank() 
{
    delete userAccountDatabase;
    delete bankAccountDatabase;
    delete currentLogin;
}

////// METHOD(S)

CURRENCY Bank::eSelectCurrency()
{
    std::cout << "Alegeti moneda contului din lista de mai jos: ";
    std::cout << "\n\n1->EURO\n";
    std::cout << "2->DOLLAR\n";
    std::cout << "3->RON\n";
    std::cout << "\nSelectie: ";
    int iChosenCurrency; std::cin >> iChosenCurrency;

    switch (iChosenCurrency)
    {
    case 1:
        return CURRENCY::EURO;
    case 2:
        return CURRENCY::DOLLAR;
    case 3:
        return CURRENCY::RON;
    default:
        return CURRENCY::UNKNOWN;
    }
}

void Bank::AddAccount()
{
    std::string sName, sSurname;
    do
    {
        system("cls");
        std::cout << "Introduceti prenumele utilizatorului (prenumele poate contine spatiu sau cratima): ";
        std::cin >> sName;

        std::cout << "Introduceti numele utlizatorului(numele poate contine spatiu sau cratima): ";
        std::cin >> sSurname;
    } while (!(bank_utilities::IsValidNameOrSurname(sName) && bank_utilities::IsValidNameOrSurname(sSurname)));

    std::string sIban{sCreateIban()};
    if (sIban == "IBAN invalid.\n")
    {
        std::cout << "Selectia este invalida. Incercati din nou.\n\n";
        sIban = sCreateIban();
    }

	BankAccount* account = new BankAccount(sName, sSurname, sIban);
    account->SetCurrencyFromIban();
	bankAccountDatabase->AddToFile(account);
    delete account;

    std::cout << "\n1 -> Pentru a mai adauga un cont\n";
    std::cout << "2 -> Pentru a reveni in meniul principal\n";
    int iOption = 0;
    std::cout << "\nSelectie: "; std::cin >> iOption;

    
    switch (iOption)
    {
    case 1:
        system("CLS");
        AddAccount();
        break;
    default:
        break;
    }
}

std::string Bank::sCreateIban()
{
    std::string sIban[6]{ "RO", "ITBK" };

    CURRENCY eUserCurrency{eSelectCurrency()};

    for (int i = 5; i > 2; i--)
    {
        (i == 5) ? srand(time(NULL)) : srand(std::stoi(sIban[i + 1]));

        sIban[i] = std::to_string(rand() % 8999 + 1000);
    }

    switch (eUserCurrency)
    {
    case CURRENCY::UNKNOWN:
        return "IBAN invalid.\n";
    case CURRENCY::EURO:
        sIban[2] = "EEUR";
        break;
    case CURRENCY::DOLLAR:
        sIban[2] = "EUSD";
        break;
    case CURRENCY::RON:
    {
        srand(std::stoi(sIban[3]));
        sIban[2] = std::to_string(rand() % 8999 + 1000);
    }
        break;
    default:
        break;
    }

    srand(time(NULL) + std::stoi(sIban[4])); std::string sValidationCode = std::to_string(rand() % 89 + 10);
    sIban[0] += sValidationCode;

    std::string sGeneratedIban;
    for (auto sequence : sIban)
        sGeneratedIban += sequence;

    return sGeneratedIban;
}

void Bank::SeeAccounts()
{
	std::cout << "Numarul de conturi din baza de date a bancii este: " << bankAccountDatabase->CountEntries();
    std::vector<std::pair<int, BankAccount*>> entries = bankAccountDatabase->ReturnAllEntriesWithIds();
	std::cout << "\n\n";

    if (!entries.empty())
    {
        std::cout.width(8); std::cout << std::left << "ID";
        std::cout.width(15); std::cout << std::left << "Prenume";
        std::cout.width(15); std::cout << std::left << "Nume";
        std::cout.width(24); std::cout << std::left << "Moneda";
        std::cout.width(28); std::cout << std::left << "IBAN";
        std::cout.width(15); std::cout << std::left << "Sold";
        std::cout << "\n\n";

        for (auto iter = entries.begin(); iter < entries.end(); iter++)
        {
            std::cout.width(8); std::cout << std::left << iter->first;
            std::cout.width(15); std::cout << std::left << iter->second->sGetName();
            std::cout.width(15); std::cout << std::left << iter->second->sGetSurname();
            std::cout.width(24); std::cout << std::left << iter->second->sGetCurrencyAsString();
            std::cout.width(28); std::cout << std::left << iter->second->sGetIban();
            std::cout.width(15); std::cout << std::left << iter->second->fGetBalance();
            std::cout << "\n";
        }
    }

    std::cout << "\n\nAPASATI ORICE TASTA PENTRU A VA INTOARCE IN MENIU...";
    system("pause > nul");
}

void Bank::mainMenu()
{
    int iOption{ 10 }; // default value, so that we avoid undefined behaviour

    while (iOption)
    {
        system("CLS");
        std::cout << "Meniul Principal\n\n";
        std::cout << "1 -> Adaugare cont\n";
        std::cout << "2 -> Vizualizare conturi\n";
        std::cout << "3 -> Modificare conturi\n";
        std::cout << "4 -> Adaugare utilizator\n";
        std::cout << "5 -> Stergeti utilizator\n\n";
        std::cout << "0 -> Inchidere aplicatie.\n\n";
        std::cout << "Introduceti optiunea: ";
        std::cin >> iOption;
        system("CLS");


        switch (iOption)
        {
        case 1:
            AddAccount();
            break;
        case 2:
            SeeAccounts();
            break;
        case 3:
            ModifyAccount();
            break;
        case 4:
            AddUserAccount();
            break;
        case 5:
            DeleteUserAccount();
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

Bank* Bank::getInstanceOfBank()
{
    if (instanceOfBank == nullptr)
        instanceOfBank = new Bank();

    return instanceOfBank;
}

void Bank::ModifyAccount()
{
    std::string sName, sSurname;
    do
    {
        system("CLS");
        std::cout << "Introduceti prenumele si numele contului pe care doriti sa il modificati: ";
        std::cin >> sName; std::cin.ignore(); std::cin >> sSurname;
    } while (!(bank_utilities::IsValidNameOrSurname(sName) && bank_utilities::IsValidNameOrSurname(sSurname)));
        
    BankAccount* tempBankAccount = nullptr;
    std::vector<std::pair<int,BankAccount*>> databaseEntries (bankAccountDatabase->FindEntriesInFile(sName + " " + sSurname));

    if (databaseEntries.size() == 0)
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
            AddAccount();
            break;
        case 2:
            ModifyAccount();
            break;
        case 0:
            break;
        default:
            break;
        }
    }
    else
    {
        int iSelectedEntryId;
        if (databaseEntries.size() > 1)
        {
            system("CLS");
            std::cout << "Au fost gasite mai multe conturi sub acelasi nume.\n"
                      << "Introduceti numarul de identificare a contului pe care doriti sa il modificati.\n\nConturi: \n\n";

            std::cout.width(8); std::cout << std::left << "ID";
            std::cout.width(15); std::cout << std::left << "Prenume";
            std::cout.width(15); std::cout << std::left << "Nume";
            std::cout.width(24); std::cout << std::left << "Moneda";
            std::cout.width(28); std::cout << std::left << "IBAN";
            std::cout.width(15); std::cout << std::left << "Sold";
            std::cout << "\n\n";

            for (auto iter = databaseEntries.begin(); iter < databaseEntries.end(); iter++)
            {
                std::cout.width(8); std::cout << std::left << iter->first;
                std::cout.width(15); std::cout << std::left << iter->second->sGetName();
                std::cout.width(15); std::cout << std::left << iter->second->sGetSurname();
                std::cout.width(24); std::cout << std::left << iter->second->sGetCurrencyAsString();
                std::cout.width(28); std::cout << std::left << iter->second->sGetIban();
                std::cout.width(15); std::cout << std::left << iter->second->fGetBalance();
                std::cout << "\n";
            }

            std::cout << "\nSelectie: ";
            std::cin >> iSelectedEntryId;

            for (auto iter = databaseEntries.begin(); iter != databaseEntries.end(); iter++)
                if (iter->first == iSelectedEntryId)
                {
                    tempBankAccount = iter->second;
                    break;
                }
        }
        else
        {
            iSelectedEntryId = databaseEntries.begin()->first;
            tempBankAccount = databaseEntries.begin()->second;
        }

        system("CLS");
        std::cout << "Ce operatie doresti sa efectuezi asupra contului?\n\n";
        std::cout << "1 -> Modifica prenume\n";
        std::cout << "2 -> Modifica nume\n";
        std::cout << "3 -> Modifica suma din cont\n";
        std::cout << "9 -> STERGETI CONTUL\n";
        std::cout << "\n0 -> Intoarcete in meniul principal\n";
        std::cout << "\nIntroduceti optiunea: ";
        int iOption;
        std::cin >> iOption;

        switch (iOption)
        {
        case 1:
            {
                std::string sNewAccName;

                do
                {
                    system("CLS");
                    std::cout << "Prenumele actual:                     " << tempBankAccount->sGetName() << '\n';
                    std::cout << "Introduceti noul prenume al contului: ";
                    std::cin >> sNewAccName;
                } while (!bank_utilities::IsValidNameOrSurname(sName));
                tempBankAccount->sSetName(sNewAccName);
                bankAccountDatabase->UpdateEntry(iSelectedEntryId, tempBankAccount);
                std::cout << "\nNumele a fost modificat cu succes!";
                std::cout << "\n\nAPASATI ORICE TASTA PENTRU A VA INTOARCE IN MENIUL PRINCIPAL...";
                system("pause > nul");
            }
            break;
        case 2:
            {
                std::string sNewAccSurname;

                do
                {
                    system("CLS");
                    std::cout << "Numele actual:                     " << tempBankAccount->sGetSurname() << '\n';
                    std::cout << "Introduceti noul nume al contului: ";
                    std::cin >> sNewAccSurname;
                } while (!bank_utilities::IsValidNameOrSurname(sName));
                tempBankAccount->sSetSurname(sNewAccSurname);
                bankAccountDatabase->UpdateEntry(iSelectedEntryId, tempBankAccount);
                std::cout << "\nPrenumele a fost modificat cu succes!";
                std::cout << "\n\nAPASATI ORICE TASTA PENTRU A VA INTOARCE IN MENIUL PRINCIPAL...";
                system("pause > nul");
            }
            break;
        case 3:
            {
                std::string sNewAccBalance;
                do
                {
                    system("CLS");
                    std::cout << "Soldul actual:         " << tempBankAccount->fGetBalance() << '\n';
                    std::cout << "Introduceti noul sold: ";
                    std::cin >> sNewAccBalance;
                } while (!bank_utilities::IsValidBalance(sNewAccBalance));
                tempBankAccount->fSetBalance(std::stod(sNewAccBalance));
                bankAccountDatabase->UpdateEntry(iSelectedEntryId, tempBankAccount);
                std::cout << "\nSoldul a fost modificat cu succes!";
                std::cout << "\n\nAPASATI ORICE TASTA PENTRU A VA INTOARCE IN MENIUL PRINCIPAL...";
                system("pause > nul");
            }
            break;
        case 9:
            {
                system("CLS");
                std::string sUserName, sUserPassword;
                std::cout << "Pentru aceasta operatiune, va rugam sa introduceti din nou numele de utilizator si parola.\n\n";
                std::cout << "Username: "; std::cin >> sUserName;
                std::cout << "Password: "; std::cin >> sUserPassword;
                UserAccount* userToValidate = new UserAccount(sUserName, sUserPassword);
                if (currentLogin->sGetUserName() == userToValidate->sGetUserName() && currentLogin->sGetUserPassword() == userToValidate->sGetUserPassword())
                {
                    delete userToValidate;
                    bankAccountDatabase->RemoveFromFile(tempBankAccount);
                    std::cout << "Contul a fost sters!\n";
                }
                else
                {
                    delete userToValidate;
                    std::cout << "ACTIUNEA A ESUAT!\n";
                    std::exit(1); // 1 - ACTION DENIED, EMERGENCY SHUTDOWN
                }
                std::cout << "\n\nAPASATI ORICE TASTA PENTRU A VA INTOARCE IN MENIUL PRINCIPAL...";
                system("pause > nul");
            }
            break;
        default:
            break;
        }
    }
}

void Bank::AddUserAccount()
{
    system("cls");
    std::string sUserName, sUserPassword;
    UserAccount* newUserAccount = nullptr;

    while (newUserAccount == nullptr)
    {
        std::cout << "Alegeti un nume de utilizator: "; std::cin >> sUserName;
        std::cout << "Alegeti o parola:              "; std::cin >> sUserPassword;

        if (newUserAccount->bIsUserNameValid(sUserName) && newUserAccount->bIsUserPasswordValid(sUserPassword))
            newUserAccount = new UserAccount(sUserName, sUserPassword);
    }

    userAccountDatabase->AddToFile(newUserAccount);

    std::cout << "\n\n1 -> Adaugati un nou cont\n";
    std::cout << "2 -> Mergeti inapoi in meniul principal\n\n";
    std::cout << "Selectie: ";
    int iOption; std::cin >> iOption;

    if (iOption == 1)
        AddUserAccount();
}

void Bank::DeleteUserAccount()
{
    system("cls");
    std::string sUserName;
    int countUsersRegistered = userAccountDatabase->CountUsersRegistered();

    std::cout << "Alegeti utilizatorul pe care doriti sa il stergeti: "; std::cin >> sUserName;

    if (sUserName == currentLogin->sGetUserName())
        std::cout << "Nu puteti sterge utilizatorul actual\n";
    else
        userAccountDatabase->RemoveFromFile(sUserName);

    if ((userAccountDatabase->CountUsersRegistered() == countUsersRegistered) && !(sUserName == currentLogin->sGetUserName()))
        std::cout << "Contul nu a fost gasit.\n";

    std::cout << "\n\n1 -> Stergeti alt cont\n";
    std::cout << "2 -> Mergeti inapoi in meniul principal\n\n";
    std::cout << "Selectie: ";
    int iOption; std::cin >> iOption;

    if (iOption == 1)
        DeleteUserAccount();
}
