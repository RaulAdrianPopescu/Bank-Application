#pragma once

#include "UserAccount.h"
#include "BankAccount.h"

/*********************************************************************************************************************************************
* Clasa FileManager este mai mult menita ca o interfata, reprezinta scheletul de pe care FileManagerUserAccounts si FileManagerBankAccounts
* se initializeaza
**********************************************************************************************************************************************/
class FileManager
{
protected:
	////// CONSTRUCTOR(S)
	FileManager(std::string fileName);	// Constructor-ul ne va initializa field-ul inputFile cu numele fisierului pe care il vom manipula

	////// DESTRUCTOR
	virtual ~FileManager(); 

	////// FIELD(S)
	std::ifstream inputFile;		   // Field in care vom deschide input file-ul pentru fiecare obiect din clasele derivate din FileManager
	std::string fileName;              // Acest field este menit sa ne retina numele fisierului odata ce acesta este deschis, relevant pentru metodele de MergeNewDataWithFile
};

class FileManagerUserAccounts : protected FileManager
{
public:

	////// CONSTRUCTOR(S)
	FileManagerUserAccounts(std::string fileName) : FileManager(fileName) {} // Folosim un initializer list prin care specificam constructor pe care il folosim si argumentul de pe baza caruia initilizam inputFile

	////// DESTRUCTOR
	~FileManagerUserAccounts();						  // Destructor-ul ne inchide fisierul pe care il manipulam

	////// METHOD(S)
	void AddToFile(std::shared_ptr<UserAccount> newUser);			    // Metoda prin care adaugam un cont de utilizator in baza de date a utilizatorilor; returnam toate datele din baza de date sub forma unui map, adaugam noul entry iar apoi facem Merge la container cu fisierul
	void RemoveFromFile(std::string sEntrySearch);						// Metoda prin care stergem un cont de utilizator din baza de date a utilizatorilor; returnam toate datele din baza de date sub forma unui map, scoatem entry-ul ce dorim sa il stergem iar apoi facem Merge la container cu fisierul
	bool IsAccessAllowed(std::shared_ptr<UserAccount> login);           // Metoda prin care determinam daca contul de utilizator initializat in Bank are acces; returnam toate datele din baza de date sub forma unui map, verificam data utilizatorul se afla in baza de date iar apoi facem Merge la container cu fisierul
	bool HasUserAccounts();												// Metoda prin care determinam daca baza de date are sau nu conturi inregistrate; returnam toate datele din contul bancar intr-un map si verificam daca sunt intrari sau nu
	int CountUsersRegistered();											// Metoda prin care returnam cate intrari sunt in baza de date a conturilor de utilizatori

private:

	////// METHOD(S)
	std::map<std::string, std::string> ReadDataFromFile();                        // Metoda prin care returnam toate elementele din baza de date sub forma unui container de tip "map", ce ne permite sa nu avem mai mult de o intrare sub acelasi nume de utilizator
	void MergeNewDataWithFile(std::map<std::string, std::string> userDatabase);   // Metoda prin care reintroducem datele din memorie in baza de date a conturilor de utilizatori; aceasta metoda trebuie cheamata tot timpul dupa ce metoda ReadDataFromFile() a fost chemata
};

class FileManagerBankAccounts : protected FileManager
{
public:

	////// CONSTRUCTOR(S)
	FileManagerBankAccounts(std::string fileName) : FileManager(fileName) {}	  // Folosim un initializer list prin care specificam constructor pe care il folosim si argumentul de pe baza caruia initilizam inputFile

	////// DESTRUCTOR
	~FileManagerBankAccounts();													  // Destructor-ul ne inchide fisierul pe care il manipulam

	////// METHOD(S)
	void AddToFile(std::shared_ptr<BankAccount> newBankAccount);											// Metoda prin care adaugam un cont bancar in baza de date bancii; returnam toate datele din baza de date sub forma vector de tip BankAccount*, adaugam noul entry iar apoi facem Merge la container cu fisierul
	void RemoveFromFile(std::shared_ptr<BankAccount> currentAccount);										// Metoda prin care stergem un cont bancar in baza de date bancii; returnam toate datele din baza de date sub forma vector de tip BankAccount*, adaugam stergem entry-ul iar apoi facem Merge la container cu fisierul
	std::vector<std::pair<int, std::shared_ptr<BankAccount>>> FindEntriesInFile(std::string sSearchTerm);   // Metoda ne returneaza intrarile din baza de date a conturilor bancare care au acelasi prenume si nume atribuit
	std::vector<std::pair<int, std::shared_ptr<BankAccount>>> ReturnAllEntriesWithIds();					// Metoda ne returneaza toate intrarile din baza de date si le atribuie cate un cod de identificare, acesta este bazat pe pozitia ce o au in fisier
	void UpdateEntry(int entryId, std::shared_ptr<BankAccount> updatedEntry);								// Metoda ne va actualiza o intrare din baza de date aflat in sub ID-ul ce il precizam; returnam toate intrarile din baza de date, apoi, schimbam elementul de la ID-ul precizat cu cel pus de noi ca argument
	int CountEntries();																						// Returneaza numarul total de intrari din baza de date a bancii

private:

	////// METHOD(S)
	std::vector<std::shared_ptr<BankAccount>> ReadDataFromFile();											// Metoda returneaza toate elementele din baza de date
	void MergeNewDataWithFile(std::vector<std::shared_ptr<BankAccount>> data);								// Metoda ne adauga toate elementele dintr-un vector de tip BankAccount* in fisierul precizat; aceasta metoda trebuie chemata tot timpul dupa ce ReadDataFromFile() a fost chemat
};