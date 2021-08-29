#pragma once

#include "UserAccount.h"
#include "BankAccount.h"

class FileManager
{
protected:
	////// CONSTRUCTOR(S)
	FileManager(std::string fileName);

	////// DESTRUCTOR
	virtual ~FileManager();

	////// FIELD(S)
	std::ifstream inputFile;
	std::string fileName;
};

class FileManagerUserAccounts : protected FileManager
{
public:

	////// CONSTRUCTOR(S)
	FileManagerUserAccounts(std::string fileName) : FileManager(fileName) {}

	////// DESTRUCTOR
	~FileManagerUserAccounts();

	////// METHOD(S)
	void AddToFile(UserAccount* newUser);
	void RemoveFromFile(std::string sEntrySearch);
	bool IsAccessAllowed(UserAccount* login);
	bool HasUserAccounts();
	int CountUsersRegistered();

private:

	////// METHOD(S)
	std::map<std::string, std::string> ReadDataFromFile();
	void MergeNewDataWithFile(std::map<std::string, std::string> userDatabase);
};

class FileManagerBankAccounts : protected FileManager
{
public:

	////// CONSTRUCTOR(S)
	FileManagerBankAccounts(std::string fileName) : FileManager(fileName) {}

	////// DESTRUCTOR
	~FileManagerBankAccounts();

	////// METHOD(S)
	void AddToFile(BankAccount* newBankAccount);
	void RemoveFromFile(BankAccount* currentAccount);
	std::vector<std::pair<int, BankAccount*>> FindEntriesInFile(std::string sSearchTerm);
	std::vector<std::pair<int, BankAccount*>> ReturnAllEntriesWithIds();
	void UpdateEntry(int entryId, BankAccount* updatedEntry);
	int CountEntries();

private:

	////// METHOD(S)
	std::vector<BankAccount*> ReadDataFromFile();
	void MergeNewDataWithFile(std::vector<BankAccount*> data);
	bool IsInFile(std::string sSearchTerm);
};