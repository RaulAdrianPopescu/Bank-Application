#pragma once

#include "Bank.h"

#include <map>
#include <fstream>
#include <utility>


class FileManager
{
public:
	////// CONSTRUCTOR(S)
	FileManager(std::string fileName);

	////// DESTRUCTOR
	~FileManager();

	////// FIELD(S)
	std::ifstream inputFile;
	std::string fileName;
};

class FileManagerUserAccounts : public FileManager
{
public:

	////// CONSTRUCTOR(S)
	FileManagerUserAccounts(std::string fileName) : FileManager(fileName) {}

	////// METHOD(S)
	void AddToFile(UserAccount* newUser);
	void RemoveFromFile(std::string sEntrySearch);

private:

	////// METHOD(S)
	std::map<std::string, std::string> ReadDataFromFile();
	void MergeNewDataWithFile(std::map<std::string, std::string> userDatabase);
	bool IsInFile(std::string sUserName);
};

class FileManagerBankAccounts : public FileManager
{
public:

	////// CONSTRUCTOR(S)
	FileManagerBankAccounts(std::string fileName) : FileManager(fileName) {}

	////// METHOD(S)
	void AddToFile(BankAccount* newBankAccount);
	void RemoveFromFile(BankAccount* currentAccount);
	std::vector<std::pair<int, BankAccount*>> FindEntriesInFile(std::string sSearchTerm);
	int CountEntries();

private:

	////// METHOD(S)
	std::vector<BankAccount*> ReadDataFromFile();
	void MergeNewDataWithFile(std::vector<BankAccount*> data);
	bool IsInFile(std::string sSearchTerm);
};