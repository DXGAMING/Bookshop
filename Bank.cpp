#include "Bank.h"
#include <Windows.h>



Bank::Bank()
{
}


Bank::~Bank()
{
}


void Bank::readBankData()
{
	std::fstream read;
	read.open(BANK_FILE, std::fstream::in);
	if (!read.is_open())
	{
		read.open(BANK_FILE, std::fstream::in);
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
				std::string email = strtok_s(dup, "|", &t);
				double balance= atof(strtok_s(nullptr, "|", &t));
				CreditCard creditCard(balance);
				bankData.emplace(email, creditCard);
			}
		}

	}
	read.close();
}


bool Bank::addToBankBase(Buyer buyer)
{
	
	readBankData();
	if (!bankData.empty())
	{
		std::map<std::string, CreditCard>::iterator iterator = bankData.begin();
		// Iterate over the map using Iterator till end.
		while (iterator != bankData.end())
		{
			if (buyer.getEmail() == iterator->first)
			{
				std::cout << "Пользователь с такими данными уже существует" << std::endl;
				clearBankData();
				return false;

			}
			else
			iterator++;

		}
			std::fstream add;
			add.open(BANK_FILE, std::fstream::out | std::fstream::app);
			add << buyer.getEmail() << "|" << buyer.getPayment().getBalance() << "\n";
			add.close();
			clearBankData();
			return true;
	}
	
}



void Bank::clearBankData()
{
	bankData.clear();
}

CreditCard Bank::getPayment(std::string email)
{
	readBankData();
	if (!bankData.empty())
	{
		CreditCard payment = bankData.find(email)->second;
		return payment;
	}
	else return NULL;
}

void Bank::substractBalance(std::string email, double sum)
{
	
	const  std::string TEMP_FILE = "C:\\Users\\Dima\\source\\repos\\Bookshop\\TEMP.txt";
	std::fstream add;
	add.open(TEMP_FILE, std::fstream::out | std::fstream::app);
	readBankData();
	if (!bankData.empty())
	{
		std::map<std::string, CreditCard>::iterator iterator = bankData.begin();
		// Iterate over the map using Iterator till end.
		while (iterator != bankData.end())
		{
			if (email == iterator->first)
			{
				double newBalance = iterator->second.getBalance() - sum;
				add << iterator->first << "|" << newBalance << '\n';
				if (newBalance == 0)
					std::cout << "Баланс пуст" << std::endl;
				
			}
			else
				add << iterator->first << "|" << iterator->second.getBalance() << '\n';
			iterator++;

		}
	}
	else
		std::cout << "Ошибка получения банковских данных" << std::endl;
	bankData.clear();
	add.close();
	DeleteFile(BANK_FILE.c_str());
	rename(TEMP_FILE.c_str(), BANK_FILE.c_str());

}