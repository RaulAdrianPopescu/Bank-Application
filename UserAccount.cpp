#include "UserAccount.h"


////// CONSTRUCTOR(S)
UserAccount::UserAccount()
{
    system("cls");
    std::string sNameInput, sPasswordInput;

    while (true)
    {
        std::cout << "Introduceti numele utilizatorului: ";
        std::getline(std::cin, sNameInput);
        if (!bIsUserNameValid(sNameInput))
            continue;

        std::cout << "Introduceti parola utilizatorului: ";
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
std::string const UserAccount::sGetUserName() { return sUserName; }
std::string const UserAccount::sGetUserPassword() { return sUserPassword; }

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