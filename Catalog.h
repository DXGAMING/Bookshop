#pragma once
#include <sstream>
#include <fstream>
#include <vector>
#include "BookForSale.h"
#include <iomanip>
class Catalog
{
	std::vector<BookForSale> assortment;
	const  std::string BOOKS_FILE ="C:\\Users\\Dima\\source\\repos\\Bookshop\\Books.txt";
public:
	void clearAssortment();
	bool checkAvailability(Book book,int amount);
	void substractOrder(std::vector<BookForSale> book);
	void substractOrder(BookForSale book);
	void deleteBook(std::string name,std::string author);
	
	void readCatalog();
	void addToCatalog(BookForSale book);
	std::vector<BookForSale> getAssortment();
};

