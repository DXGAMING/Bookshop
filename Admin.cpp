#include "Admin.h"
#include "Windows.h"
#include <iomanip>
#include "ValidData.h"
#include <map>
#include <algorithm>
Admin::Admin(std::string email, std::string password){

	this->email = email;
	this->password = password;
	this->userType = "admin";
}

Admin::~Admin(){

}

void Admin::addBook(){  // сделать так чтобы если книга уже есть увеличивало просто количество данной книги

	
	std::string name, author;
	double price;
	int amount;
	
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "Введите название книги" << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin,name);
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	SetConsoleCP(866);
	std::cout << "Введите автора книги" << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin, author);
	SetConsoleCP(866);
	std::cout << "Введите стоимость книги" << std::endl;
	price = ValidData<double>::getValidValue("Введите корректное числовое значение");
	std::cout << "Введите количество книг" << std::endl;
	amount = ValidData<int>::getValidValue("Введите корректное числовое значение");
	Book book(name, author, price);
	BookForSale book4Sale(book, amount);
	assortment.addToCatalog(book4Sale);
	
}

void Admin::findBook() 
{
	system("cls");
	std::string toFind;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "Поиск : " << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin, toFind);
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	SetConsoleCP(866);
	assortment.readCatalog();
	std::vector<BookForSale> catalogToFind;
	catalogToFind = assortment.getAssortment();
	bool isFound = false;
	for (auto book : catalogToFind)
	{
		int index = (book.getBook().getName()+book.getBook().getAuthor()+std::to_string(book.getBook().getPrice())+std::to_string(book.getAmount())).find(toFind);
		if (index != std::string::npos)
		{
			std::cout << "|" << std::setw(25)<< book.getBook().getName() + "|" << std::setw(25) << book.getBook().getAuthor() + "|" << std::setw(12) <<
				std::to_string(book.getBook().getPrice()) + "р|" << std::setw(5) << std::to_string(book.getAmount()) <<"шт|" << std::endl;
			isFound = true;
		}
	}
	if (!isFound)
		std::cout << "По данному запросу ничего не найдено" << std::endl;
	assortment.clearAssortment();
	system("pause");
}
void Admin::deleteBook()
{
	std::string name, author;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cout << "Введите название книги" << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin, name);
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	SetConsoleCP(866);
	std::cout << "Введите автора книги" << std::endl;
	SetConsoleCP(1251);
	std::getline(std::cin, author);
	SetConsoleCP(866);
	assortment.deleteBook(name,author);
}

void Admin::readLog()
{
	std::vector<BookForSale> soldItems;
	std::string LOG_FILE = "C:\\Users\\Dima\\source\\repos\\Bookshop\\Log.txt";
	std::fstream read;
	read.open(LOG_FILE, std::fstream::in);
	if (!read.is_open())
	{
		read.open(LOG_FILE, std::fstream::in);
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
				std::string login = strtok_s(dup, "|", &t);
				std::string name = strtok_s(nullptr, "|", &t);
				std::string author = "";
				int amount = atoi(strtok_s(nullptr, "|", &t));
				double price = atof(strtok_s(nullptr, "|", &t)) / amount;

				Book book(name, author, price);
				BookForSale book4sale(book, amount);
				soldItems.push_back(book4sale);
			}
		}
		std::map<std::string, int> popularity;
		for (int i = 0; i < soldItems.size(); ++i)
		{
			if (!popularity.empty())
			{
				auto search = popularity.find(soldItems[i].getBook().getName());
				if (search != popularity.end())
				{
					//int oldAmount = search->second;
					//std::string oldString = search->first;
					//popularity.erase(search);
					search->second += soldItems[i].getAmount();
					//popularity.emplace(oldString, (oldAmount + soldItems[i].getAmount()));

				}
				else
					popularity.emplace(soldItems[i].getBook().getName(), soldItems[i].getAmount());
			}
			else
				popularity.emplace(soldItems[i].getBook().getName(), soldItems[i].getAmount());
		}
		if (!popularity.empty()) {
			std::map<std::string, int>::iterator iterator = popularity.begin();
			// Iterate over the map using Iterator till end.
			struct
			{
				std::string popNames;
				int popAmount;
			}typedef pops;

			std::vector<pops> finalPopItems;
			while (iterator != popularity.end())
			{
				pops pop;
				pop.popNames = iterator->first;
				pop.popAmount = iterator->second;
				finalPopItems.push_back(pop);
				iterator++;
			}
			if (!finalPopItems.empty()) {
				std::sort(finalPopItems.begin(), finalPopItems.end(), [](pops pop1, pops pop2) {return pop1.popAmount > pop2.popAmount; });
				std::cout << "\t|" << std::setw(25) << " Название книги      " << "|" << std::setw(20) <<
					"   Кол-во проданных единиц    " << "|" << std::endl;
				std::cout << "\t|" << std::setw(25) << "_________________________" << "|" << std::setw(20) <<
					"______________________________" << "|" << std::endl;
				for (auto item : finalPopItems)
				{
					std::cout << "\t|" << std::setw(25) << item.popNames << "|" << std::setw(30) <<
						item.popAmount << "|" << std::endl;
				}
				std::cout << "\t|" << std::setw(25) << "_________________________" << "|" << std::setw(20) <<
					"______________________________" << "|" << std::endl;
			}
			system("pause");
		}
	}
	read.close();
}

void Admin::showInput()
{
	std::vector<BookForSale> soldItems;
	std::string LOG_FILE = "C:\\Users\\Dima\\source\\repos\\Bookshop\\Log.txt";
	std::fstream read;
	read.open(LOG_FILE, std::fstream::in);
	if (!read.is_open())
	{
		read.open(LOG_FILE, std::fstream::in);
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
				std::string login = strtok_s(dup, "|", &t);
				std::string name = strtok_s(nullptr, "|", &t);
				std::string author = "";
				int amount = atoi(strtok_s(nullptr, "|", &t));
				double price = atof(strtok_s(nullptr, "|", &t)) / amount;

				Book book(name, author, price);
				BookForSale book4sale(book, amount);
				soldItems.push_back(book4sale);
			}
		}
		int sum = 0;
		if (!soldItems.empty()) {
			for (auto item : soldItems)
			{
				sum += (item.getBook().getPrice() * item.getAmount());
			}
			std::cout << "Общая выручка составила : " << sum  << "рублей" << std::endl;
		}
		system("pause");
	}
}