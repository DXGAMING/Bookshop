#include "UserBase.h"



std::vector<User*> UserBase::getAccounts()
{
	return accounts;
}

UserBase::UserBase()
{
}


UserBase::~UserBase()
{
}

void UserBase::readAccounts()
{
	std::fstream read;
	read.open(ACCOUNTS_FILE, std::fstream::in);
	if (!read.is_open())
	{
		read.open(ACCOUNTS_FILE, std::fstream::in);
	}
	else {
		std::string buf;
		while (!read.eof())
		{
			buf.clear();
			getline(read, buf, '\n');
			if (buf.size() != 0)
			{
				char* dup = new char(strlen(buf.c_str()) + 1);
				dup = _strdup(buf.c_str());
				char* t = nullptr;
				std::string email = crypter.decrypt(strtok_s(dup, "|", &t),12345);
				std::string password =    crypter.decrypt(strtok_s(nullptr, "|", &t),12345);
				std::string userType = crypter.decrypt(strtok_s(nullptr, "|", &t),12345);
				
				
				if (userType == "admin")
				{
					Admin* adminptr = new Admin(email, password);
					this->accounts.push_back(adminptr);
				}
				else if (userType == "buyer")
				{
					Buyer* buyerptr = new Buyer(email, password);
					this->accounts.push_back(buyerptr);
				}

				
			}
		}

	}
	read.close();
}

void UserBase::clearAccounts()
{
	this->accounts.clear();
}
void UserBase::addToUserBase(User* user)
{
	readAccounts();
	if (!accounts.empty())
	{
		for (auto acc : accounts)
		{
			if (acc->equals(user))
			{
				std::cout << "ѕользователь с такими данными уже существует " << std::endl;
				return;
			}
		}
	}
	std::fstream add;
	add.open(ACCOUNTS_FILE, std::fstream::out | std::fstream::app);
	add << crypter.encrypt(user->getEmail(),12345) << "|" << crypter.encrypt(user->getPassword(), 12345) <<"|" <<
		crypter.encrypt(user->getUserType(), 12345)	 << '\n';
	add.close();
}
