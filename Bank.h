#pragma once
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include "Buyer.h"
class Bank
{
	std::map<std::string, CreditCard > bankData;
	const std::string BANK_FILE = "C:\\Users\\Dima\\source\\repos\\Bookshop\\Bank.txt";
public:
	Bank();
	~Bank();
	void readBankData();
	bool addToBankBase(Buyer buyer);

	void clearBankData();
	CreditCard getPayment(std::string email);
	void substractBalance(std::string email, double sum);
};

