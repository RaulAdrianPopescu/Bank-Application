#include "Bank.h"
#include <ctime>

/////////////////  BANK \\\\\\\\\\\\\\\\\\

////// CONSTRUCTOR(S)
Bank::Bank() 
{
    bankAccountDatabase = new FileManagerBankAccounts("bank_accounts.csv");
}

////// DESTRUCTOR
Bank::~Bank() 
{ 
    for (auto iter = vBankAccounts.begin(); iter != vBankAccounts.end(); iter++)
    {
        BankAccount* toRemove = *iter;
        delete toRemove;
    }

    vBankAccounts.clear();
    delete bankAccountDatabase;
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

void Bank::vAddAccount()
{
	std::cout << "Introduceti prenumele utilizatorului: ";
	std::string sSurname;
	std::cin >> sSurname;

	std::cout << "Introduceti numele utlizatorului: ";
	std::string sName;
	std::cin >> sName;

    std::string sIban{sCreateIban()};
    if (sIban == "IBAN invalid.\n")
    {
        std::cout << "Selectia este invalida. Incercati din nou.\n\n";
        sIban = sCreateIban();
    }

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

std::string Bank::sCreateIban()
{
    std::string sIban[6]{ "RO", "ITBK" };

    CURRENCY eUserCurrency{eSelectCurrency()};

    for (int i = 5; i > 2; i--)
    {
        (i == 5) ? srand(time(NULL)) : srand(std::stoi(sIban[i + 1]));

        sIban[i] = std::to_string(rand() % 9999 + 1000);
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

void Bank::vSeeAccounts() const
{
	std::cout << "Numarul de conturi din baza de date a bancii este: " << vBankAccounts.size();
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
    std::cin >> sName; std::cin.ignore();
    std::cin >> sSurname;

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
        std::cout << "1 -> Modifica prenume\n";
        std::cout << "2 -> Modifica nume\n";
        std::cout << "3 -> Modifica suma din cont\n";
        std::cout << "\n0 -> Intoarcete in meniul principal\n";
        std::cout << "\nIntroduceti optiunea: ";
        int iOption;
        std::cin >> iOption;
        system("CLS");

        switch (iOption)
        {
        case 1:
        {
            std::cout << "Introduceti noul prenume al contului: ";
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
            std::cout << "Introduceti noul nume al contului: ";
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



/////////////////  USER ACCOUNT \\\\\\\\\\\\\\\\\\

////// CONSTRUCTOR(S)
UserAccount::UserAccount()
{
    system("cls");
    std::string sNameInput, sPasswordInput;

    while (true)
    {
        std::cout << "Introduceti numele utilizatorul: ";
        std::getline(std::cin, sNameInput);
        if (!bIsUserNameValid(sNameInput))
            continue; 

        std::cout << "Introduceti parola utilizatorul: ";
        std::getline(std::cin, sPasswordInput);
        if (!bIsUserPasswordValid(sPasswordInput))
            continue;
        
        break;
    }

    sSetUserName(sNameInput);
    sSetUserPassword(sPasswordInput);

    system("cls");
}

UserAccount::UserAccount(std::string sName, std::string sPassword)
{
        sSetUserName(sName);
        sSetUserPassword(sPassword);
}

////// DESTRUCTOR
UserAccount::~UserAccount() {}

////// GETTER(S)
std::string const UserAccount::sGetUserName(){ return sUserName; }
std::string const UserAccount::sGetUserPassword(){ return sUserPassword; }

////// SETTER(S)
void UserAccount::sSetUserName(std::string& sInputName) { sUserName = sInputName; }
void UserAccount::sSetUserPassword(std::string& sInputPassword) { sUserPassword = sInputPassword; }

bool UserAccount::bIsUserNameValid(std::string sInputName)
{
    if (sInputName.size() >= 6 && sInputName.size() <= 16)
    {
        for (int i = 0; i < sInputName.size(); i++)
        {
            if (std::isspace(sInputName[i]))
            {
                system("CLS");
                std::cout << "\nVa rugam sa nu folositi spatii in numele utilizatorului.\n\n";
                return false;
            }
        }
    }
    else 
    { 
        system("CLS");
        std::cout << "\nVa rugam sa va asigurati ca introduceti un nume alcatuit din minim 6, maxim 16, caractere.\n\n";
        return false;
    }

    return true;
}

bool UserAccount::bIsUserPasswordValid(std::string sInputPassword)
{
    int uppercaseCount = 0;
    int alphaNumCount = 0; 
    int specialCharCount = 0;

    if (sInputPassword.size() >= 6 && sInputPassword.size() <= 16)
    {
        for (int i = 0; i < sInputPassword.size(); i++)
        {
            if (std::isalnum(sInputPassword[i]) && !(std::isupper(sInputPassword[i])))
                alphaNumCount++;
            else if (std::ispunct(sInputPassword[i]))
                specialCharCount++;
            else if (std::isupper(sInputPassword[i]))
                uppercaseCount++;
            else if (std::isspace(sInputPassword[i]))
            {
                system("CLS");
                std::cout << "\nVa rugam sa nu folositi spatii in numele utilizatorului.\n\n";
                return false;
            }
        }
    }
    else
    {
        std::cout << "\nVa rugam sa va asigurati ca introduceti o parola alcatuita din minim 6, maxim 16, caractere.\n\n";
        return false;
    }

    if (alphaNumCount < 4 || specialCharCount < 1 || uppercaseCount < 1)
    {
        std::cout << "\nVa rugam sa va asigurati ca parola introdusa este alcatuita din cel putin: o majuscula, un caracter special si patru caractere mici.\n\n";
        return false;
    }
    return true;
}

bool UserAccount::bDoesAccountHaveAccess(UserAccount* adminAccount)
{
    if (!(bIsUserNameValid(this->sGetUserName())) || !(bIsUserPasswordValid(this->sGetUserPassword())))
    {
        std::cout << "\n\nAPASATI ORICE TASTA PENTRU A REINCERCA...\n\n";
        system("pause > nul");
        system("CLS");
        return false;
    }
    else if (adminAccount->sGetUserName() != this->sGetUserName())
    {
        std::cout << "\nNumele/parola contului este incorect(a).";
        std::cout << "\n\nAPASATI ORICE TASTA PENTRU A REINCERCA...\n\n";
        system("pause > nul");
        system("CLS");
        return false;
    }
    else if (adminAccount->sGetUserPassword() != this->sGetUserPassword())
    {
        std::cout << "\nNumele/parola contului este incorect(a).";
        std::cout << "\n\nAPASATI ORICE TASTA PENTRU A REINCERCA...\n\n";
        system("pause > nul");
        system("CLS");
        return false;
    }
    else
        return true;
}