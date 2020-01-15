#include "CreditCard.h"



CreditCard::CreditCard()
{
}

CreditCard::CreditCard(double balance)
{
	this->balance = balance;
}

double CreditCard::getBalance() 
{
	return balance;
}

CreditCard::~CreditCard()
{
}

void CreditCard::pay(double paymentValue)
{
	balance -= paymentValue;
}
