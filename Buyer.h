#pragma once
#include "CreditCard.h"
#include "User.h"
#include "Catalog.h"
class Buyer :
	public User
{
	Catalog catalog;
	CreditCard payment;
public:
	Buyer();
	Buyer(std::string email, std::string password);
	Buyer(std::string email, std::string password, CreditCard payment);

	CreditCard getPayment();

	// добавить поля name и у CreditCard пароль от карты и хранить данные
	~Buyer();
	void pay(double paymentValue);

	void findBook() override;


};

