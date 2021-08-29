#pragma once

#include "STL.h"

class UserAccount
{
public:

	////// CONSTRUCTOR(S)
	UserAccount();
	UserAccount(std::string sName, std::string sPassword);

	////// DESTRUCTOR
	~UserAccount();

	////// GETTER(S)
	std::string const sGetUserName();
	std::string const sGetUserPassword();

	////// METHOD(S)
	bool bIsUserNameValid(std::string sInputName);
	bool bIsUserPasswordValid(std::string sInputPassword);
	bool bDoesAccountHaveAccess(UserAccount* adminAccount);

private:

	////// FIELD(S)
	void sSetUserName(std::string& sInputName);
	void sSetUserPassword(std::string& sInputPassword);
	std::string sUserName;
	std::string sUserPassword;
};