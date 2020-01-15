#pragma once
#include "ICryptData.h"
#include <vector>
#include <fstream>
#include "User.h"
#include "Admin.h"
#include "Buyer.h"
class UserBase
{
	crypto::ICryptData crypter;
	std::vector<User*> accounts;
	const std::string ACCOUNTS_FILE = "C:\\Users\\Dima\\source\\repos\\Bookshop\\Accounts.txt";
	
public:
	std::vector<User*> getAccounts();
	UserBase();
	~UserBase();
	void readAccounts();
	void clearAccounts();
	void addToUserBase(User* acc);
};
