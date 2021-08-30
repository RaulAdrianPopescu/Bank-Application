#include "FileManager.h"

/////////////////  FILE MANAGER \\\\\\\\\\\\\\\\\\

FileManager::FileManager(std::string fileName)
{
    inputFile.open(fileName, std::ios::in);
    this->fileName = fileName;
}

FileManager::~FileManager()
{
    inputFile.close();
}

/////////////////  FILE MANAGER USER ACCOUNTS \\\\\\\\\\\\\\\\\\

FileManagerUserAccounts::~FileManagerUserAccounts()
{
    inputFile.close();
}

////// PUBLIC METHOD(S) 
void FileManagerUserAccounts::AddToFile(UserAccount* newUser)
{
    std::map <std::string, std::string> dataFromFile = ReadDataFromFile();

    if (dataFromFile.find(newUser->sGetUserName()) != dataFromFile.end())
        std::cout << "\nUtilizatorul exista deja in baza de date. Va rugam incercati un alt nume de utilizator.\n";

    else
    {
        std::pair <std::string, std::string> newUserPair = { newUser->sGetUserName(), newUser->sGetUserPassword() };
        dataFromFile.insert(newUserPair);
    }

    MergeNewDataWithFile(dataFromFile);
}

void FileManagerUserAccounts::RemoveFromFile(std::string sEntrySearch)
{
    std::map<std::string, std::string> dataFromFile = ReadDataFromFile();

    for (auto iter = dataFromFile.begin(); iter != dataFromFile.end(); iter++)
        if (iter->first == sEntrySearch)
        {
            dataFromFile.erase(sEntrySearch);
            std::cout << "\nUtilizatorul a fost sters cu succes!\n";
            break;
        }

    MergeNewDataWithFile(dataFromFile);
}

bool FileManagerUserAccounts::IsAccessAllowed(UserAccount* login)
{
    std::map<std::string, std::string> users = ReadDataFromFile();

    for (auto iter = users.begin(); iter != users.end(); iter++)
        if (iter->first == login->sGetUserName() && iter->second == login->sGetUserPassword())
        {
            MergeNewDataWithFile(users);
            return true;
        }

    MergeNewDataWithFile(users);
    return false;
}

bool FileManagerUserAccounts::HasUserAccounts()
{
    int countEntries = CountUsersRegistered();
    return (countEntries > 0) ? true : false;
}

int FileManagerUserAccounts::CountUsersRegistered()
{
    std::map<std::string, std::string> dataFromFile = ReadDataFromFile();
    int countEntries = dataFromFile.size();

    MergeNewDataWithFile(dataFromFile);
    return countEntries;
}

////// PRIVATE METHOD(S)
std::map<std::string, std::string> FileManagerUserAccounts::ReadDataFromFile()
{
    std::map<std::string, std::string> fileData;
    std::string sDataFieldFromFile;

    while (std::getline(inputFile, sDataFieldFromFile, '\n'))
    {
        std::pair <std::string, std::string> userAccount;
        userAccount.first = sDataFieldFromFile.substr(0, sDataFieldFromFile.find(','));
        sDataFieldFromFile = sDataFieldFromFile.substr(sDataFieldFromFile.find(','), std::string::npos);
        userAccount.second = sDataFieldFromFile.substr(sDataFieldFromFile.find(',') + 1);

        fileData.insert(userAccount);
    }

    return fileData;
}

void FileManagerUserAccounts::MergeNewDataWithFile(std::map<std::string, std::string> data)
{
    std::string outputDataFileName = "new_" + fileName;
    std::ofstream outputFile(outputDataFileName);

    for (auto iter = data.begin(); iter != data.end(); iter++)
        outputFile << iter->first << ',' << iter->second << '\n';

    inputFile.close();
    outputFile.close();


    std::remove(fileName.c_str());
    std::rename(outputDataFileName.c_str(), fileName.c_str());


    inputFile.open(fileName, std::ios::in);
}

/////////////////  FILE MANAGER BANK ACCOUNTS \\\\\\\\\\\\\\\\\\

FileManagerBankAccounts::~FileManagerBankAccounts()
{
    inputFile.close();
}

////// PUBLIC METHOD(S)
void FileManagerBankAccounts::AddToFile(BankAccount* newBankAccount)
{
    std::vector<BankAccount*> dataFromFile = ReadDataFromFile();
    dataFromFile.push_back(newBankAccount);

    MergeNewDataWithFile(dataFromFile);
}

void FileManagerBankAccounts::RemoveFromFile(BankAccount* currentAccount)
{
    std::vector<BankAccount*> dataFromFile = ReadDataFromFile();

    for (auto iter = dataFromFile.begin(); iter != dataFromFile.end(); iter++)
        if ((*iter)->sGetIban() == currentAccount->sGetIban())
        {
            BankAccount* toRemove = *iter;
            delete toRemove;
            dataFromFile.erase(iter);
            break;
        }

    MergeNewDataWithFile(dataFromFile);
}

std::vector<std::pair<int, BankAccount*>> FileManagerBankAccounts::FindEntriesInFile(std::string sSearchTerm)
{
    std::vector<BankAccount*> dataFromFile = ReadDataFromFile();
    std::vector<std::pair<int, BankAccount*>> accountsFound;

    for (int i = 0; i < dataFromFile.size(); i++)
    {
        std::string dataNameSurname = dataFromFile.at(i)->sGetName().append(" ");
        dataNameSurname.append(dataFromFile.at(i)->sGetSurname());

        if (dataNameSurname.compare(sSearchTerm) == 0)
            accountsFound.push_back({ i + 1, dataFromFile.at(i) });
    }

    MergeNewDataWithFile(dataFromFile);
    return accountsFound;
}

std::vector<std::pair<int, BankAccount*>> FileManagerBankAccounts::ReturnAllEntriesWithIds()
{
    std::vector<BankAccount*> entries = ReadDataFromFile();
    std::vector<std::pair<int, BankAccount*>> entriesWithId;

    if (!entries.empty())
        for (int i = 0; i < entries.size(); i++)
            entriesWithId.push_back({ i + 1, entries.at(i) });

    MergeNewDataWithFile(entries);
    return entriesWithId;
}

void FileManagerBankAccounts::UpdateEntry(int entryId, BankAccount* updatedEntry)
{
    std::vector<BankAccount*> dataFromFile = ReadDataFromFile();
    dataFromFile[entryId - 1] = updatedEntry;

    MergeNewDataWithFile(dataFromFile);
}

int FileManagerBankAccounts::CountEntries()
{
    std::vector<BankAccount*> dataFromFile = ReadDataFromFile();
    MergeNewDataWithFile(dataFromFile);

    return dataFromFile.size();
}

////// PRIVATE METHOD(S)
std::vector<BankAccount*> FileManagerBankAccounts::ReadDataFromFile()
{
    std::vector<BankAccount*> fileData;
    std::string sDataFieldFromFile;

    while (std::getline(inputFile, sDataFieldFromFile, '\n'))
    {
        std::string sAccountName = sDataFieldFromFile.substr(0, sDataFieldFromFile.find(','));
        sDataFieldFromFile = sDataFieldFromFile.substr(sDataFieldFromFile.find(',') + 1);

        std::string sAccountSurname = sDataFieldFromFile.substr(0, sDataFieldFromFile.find(','));
        sDataFieldFromFile = sDataFieldFromFile.substr(sDataFieldFromFile.find(',') + 1);

        CURRENCY eAccountCurrency = static_cast<CURRENCY> (std::stoi(sDataFieldFromFile.substr(0, sDataFieldFromFile.find(','))));
        sDataFieldFromFile = sDataFieldFromFile.substr(sDataFieldFromFile.find(',') + 1);

        std::string sAccountIban = sDataFieldFromFile.substr(0, sDataFieldFromFile.find(','));
        sDataFieldFromFile = sDataFieldFromFile.substr(sDataFieldFromFile.find(',') + 1);

        double fAccountBalance = std::stod(sDataFieldFromFile.substr(0, std::string::npos));

        BankAccount* bankAccount = new BankAccount(sAccountName, sAccountSurname, eAccountCurrency, sAccountIban, fAccountBalance);
        fileData.push_back(bankAccount);
    }

    return fileData;
}

void FileManagerBankAccounts::MergeNewDataWithFile(std::vector<BankAccount*> data)
{
    std::string outputDataFileName = "new_" + fileName;
    std::ofstream outputFile(outputDataFileName);

    for (auto iter = data.begin(); iter != data.end(); iter++)
    {
        outputFile << (*iter)->sGetName() << ',' << (*iter)->sGetSurname() << ',' << std::to_string((int)((*iter)->eGetCurrency())) << ','
            << (*iter)->sGetIban() << ',' << std::to_string((*iter)->fGetBalance()) << '\n';

    }
    inputFile.close();
    outputFile.close();


    std::remove(fileName.c_str());
    std::rename(outputDataFileName.c_str(), fileName.c_str());


    inputFile.open(fileName, std::ios::in);
}