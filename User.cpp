#include "User.h"

User::User()
{

}

User::User(std::string email, std::string password,std::string userType)
{
	this->email = email;
	this->password = password;
	this->userType = userType;
}



std::string User::getEmail()
{
	return this->email;
}

std::string User::getPassword()
{
	return this->password;
}

std::string User::getUserType()
{
	return this->userType;
}

std::string User::toString()
{
	return email + "|" + password + "|" + userType;
}

bool User::equals(User* user)
{
	if (user->getEmail() == email)
		return true;
	return false;
}



