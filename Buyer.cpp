#include "Buyer.h"
#include <Windows.h>



Buyer::Buyer()
{

}
Buyer::Buyer(std::string email, std::string password)
{

	this->email = email;
	this->password = password;
	this->userType = "buyer";
	
}
Buyer::Buyer(std::string email, std::string password,CreditCard card)
{

	this->email = email;
	this->password = password;
	this->payment = card;
	this->userType = "buyer";
}

CreditCard Buyer::getPayment() 
{
	return payment;
}

Buyer::~Buyer()
{

}
void Buyer ::pay(double paymentValue)
{
	payment.pay(paymentValue);
}

void Buyer::findBook()
{
	std::string toFind;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "Поиск : " << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin, toFind);
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	SetConsoleCP(866);
	catalog.readCatalog();
	std::vector<BookForSale> catalogToFind;
	catalogToFind = catalog.getAssortment();
	bool isFound = false;
	for (auto book : catalogToFind)
	{
		int index = (book.getBook().getName() + book.getBook().getAuthor()).find(toFind);
		if (index != std::string::npos) {
			std::cout << "\t" << "|" << std::setw(25) << book.getBook().getName() + "|" << std::setw(25) << book.getBook().getAuthor() + "|" << std::setw(12) <<
				std::to_string(book.getBook().getPrice()) + "р|" << std::setw(5) << std::to_string(book.getAmount()) <<"шт|" << std::endl;
			isFound = true;
		}
	}
	if(!isFound)
		std::cout << "По данному запросу ничего не найдено" << std::endl;
	system("pause");
	catalog.clearAssortment();
}