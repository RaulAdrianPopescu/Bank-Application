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

////// PUBLIC METHOD(S) 
void FileManagerUserAccounts::AddToFile(UserAccount* newUser)
{
	std::map <std::string, std::string> dataFromFile = ReadDataFromFile();

	if (IsInFile(newUser->sGetUserName()))
		std::cout << "Utilizatorul deja exista. Va rugam incercati un alt nume de utilizator.\n";
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
	
	if (IsInFile(sEntrySearch))
	{
		dataFromFile.erase(sEntrySearch);
		std::cout << "Utilizatorul a fost sters cu succes!\n";
	}

	MergeNewDataWithFile(dataFromFile);
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


bool FileManagerUserAccounts::IsInFile(std::string sUserName)
{
	std::map <std::string, std::string> dataFromFile = ReadDataFromFile();
	bool isInFile = (dataFromFile.find(sUserName) != dataFromFile.end());
	
	MergeNewDataWithFile(dataFromFile);
	return isInFile;
}



/////////////////  FILE MANAGER BANK ACCOUNTS \\\\\\\\\\\\\\\\\\

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
			dataFromFile.erase(iter);
			delete toRemove;
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
		if (IsInFile(sSearchTerm))
		{
			std::pair<int, BankAccount*> accountFound = { i + 1, dataFromFile.at(i) };
			accountsFound.push_back(accountFound);
		}
	}

	MergeNewDataWithFile(dataFromFile);
	return accountsFound;
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

		std::string sAccountSurname = sDataFieldFromFile.substr(sDataFieldFromFile.find(','), std::string::npos);
		sDataFieldFromFile = sDataFieldFromFile.substr(sDataFieldFromFile.find(',') + 1);

		CURRENCY eAccountCurrency = static_cast<CURRENCY> (std::stoi(sDataFieldFromFile.substr(sDataFieldFromFile.find(',') + 1)));
		sDataFieldFromFile = sDataFieldFromFile.substr(sDataFieldFromFile.find(',') + 1);

		std::string sAccountIban;
		sDataFieldFromFile = sDataFieldFromFile.substr(sDataFieldFromFile.find(',') + 1);

		double fAccountBalance;
		sDataFieldFromFile = std::stod(sDataFieldFromFile.substr(sDataFieldFromFile.find(',') + 1));

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

bool FileManagerBankAccounts::IsInFile(std::string sSearchTerm)
{
	std::vector<BankAccount*> dataFromFile = ReadDataFromFile();
	bool isInFile = false;

	for (auto iter = dataFromFile.begin(); iter != dataFromFile.end(); iter++)
		if (((*iter)->sGetName() + ' ' + (*iter)->sGetSurname()) == sSearchTerm)
		{
			isInFile = true;
			break;
		}

	MergeNewDataWithFile(dataFromFile);
	return isInFile;
}