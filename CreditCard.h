#pragma once
class CreditCard
{
	double balance;
	
public:
	CreditCard();
	CreditCard(double balance);
	double getBalance();
	~CreditCard();
	void pay(double paymentValue);
};

