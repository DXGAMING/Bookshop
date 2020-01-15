#include "Catalog.h"
#include <windows.h>
void Catalog::readCatalog()
{
	std::fstream read;
	read.open(BOOKS_FILE, std::fstream::in);
	if (!read.is_open()) 
	{
		read.open(BOOKS_FILE, std::fstream::in);
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
				std::string name = strtok_s(dup, "|", &t);
				std::string author = strtok_s(nullptr, "|", &t);
				double price = atof(strtok_s(nullptr, "|", &t));
				int amount = atoi(strtok_s(nullptr, "|", &t));

				Book book(name, author, price);
				BookForSale book4sale(book, amount);
				this->assortment.push_back(book4sale);
			}
		}
	
	}
	read.close();
}

void Catalog::addToCatalog(BookForSale book) // кроме того включает в себ€ ф-ию редактировани€ цены

{
	bool isSimilar = false;
	readCatalog();
	if (!assortment.empty())
	{
		for (auto item : assortment)
		{
			if (item.equals(book))
			{
				isSimilar = true;
				DeleteFile(BOOKS_FILE.c_str());
				deleteBook(item.getBook().getName(), item.getBook().getAuthor());
				std::fstream add;
				add.open(BOOKS_FILE.c_str(), std::fstream::out | std::fstream::app);
				add << book.getBook().getName() + "|" << book.getBook().getAuthor() + "|" <<
					std::to_string(book.getBook().getPrice()) + "|" << std::to_string(item.getAmount() + book.getAmount()) << '\n';
				assortment.clear();
				add.close();
			}
		}
	}
	if (!isSimilar)
	{
		std::fstream add;
		add.open(BOOKS_FILE, std::fstream::out | std::fstream::app);
		add << book.getBook().getName() + "|"  << book.getBook().getAuthor() + "|"  <<
			std::to_string(book.getBook().getPrice()) + "|" << std::to_string(book.getAmount()) << '\n';
		add.close();
		assortment.clear();
	}
	
}

std::vector<BookForSale> Catalog::getAssortment()
{
	return this->assortment;
}

void Catalog::clearAssortment()
{
	this->assortment.clear();
}

 
bool Catalog ::checkAvailability(Book book, int amount)
{
	readCatalog();
	for (auto item : assortment)
	{
		if (item.getBook().equals(book))
		{
			if (item.getAmount() < amount)
			{
				assortment.clear();
				return false;
			}
		}
	}
	assortment.clear();
	return true;
}

void Catalog::substractOrder(std::vector<BookForSale> cart)
{
	const  std::string TEMP_FILE = "C:\\Users\\Dima\\source\\repos\\Bookshop\\TEMP.txt";
	std::fstream add;
	add.open(TEMP_FILE, std::fstream::out | std::fstream::app);
	readCatalog();
	bool isInCart = false;
	for (auto item : assortment)
	{
		int bookAmount = 0;
		for (auto bookToSell : cart)
		{
			if (item.equals(bookToSell))
			{
				bookAmount = bookToSell.getAmount();
				isInCart = true;
			}
		}
		if (isInCart)
		{
			if (item.getAmount() - bookAmount != 0)
			{
				add  << item.getBook().getName() + "|" << item.getBook().getAuthor() + "|" <<
					std::to_string(item.getBook().getPrice()) + "|" << std::to_string(item.getAmount()-bookAmount) << '\n';
			}
			else
				continue;
		}
		else
		{
			add << item.getBook().getName() + "|"  << item.getBook().getAuthor() + "|" <<
				std::to_string(item.getBook().getPrice()) + "|" << std::to_string(item.getAmount()) << '\n';

		}
			
	}
	assortment.clear();
	add.close();
	DeleteFile(BOOKS_FILE.c_str());
	rename(TEMP_FILE.c_str(), BOOKS_FILE.c_str());
	
}

void Catalog::substractOrder(BookForSale book)
{
}

void Catalog::deleteBook(std::string name,std::string author)
{
	readCatalog();
	const  std::string TEMP_FILE = "C:\\Users\\Dima\\source\\repos\\Bookshop\\TEMP.txt";

	bool isDeleted = false;
	for(auto item : assortment)
	{
		if (item.getBook().getName()!=name && item.getBook().getAuthor() != author)
		{
			isDeleted = true;
			std::fstream add;
			add.open(TEMP_FILE, std::fstream::out | std::fstream::app);
			add << item.getBook().getName() + "|" << item.getBook().getAuthor() + "|" <<
				std::to_string(item.getBook().getPrice()) + "|" << std::to_string(item.getAmount()) << '\n';
			add.close();
		}
	}
	if (isDeleted)
	{
		DeleteFile(BOOKS_FILE.c_str());
		rename(TEMP_FILE.c_str(), BOOKS_FILE.c_str());
	}

	assortment.clear();
}


