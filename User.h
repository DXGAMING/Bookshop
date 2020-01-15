#pragma once
#include <string>
#include <iostream>
class User 
{
protected:
	std::string email;
	std::string password;
	std::string userType;
	
public:
	User();
	User(std::string email, std::string password, std::string userType);
	std::string getEmail();
	std::string getPassword();
	std::string getUserType();
	virtual std::string toString();
	bool equals(User* user);
	virtual void findBook()=0;
};

