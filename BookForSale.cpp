#include "BookForSale.h"
#include <iomanip>
BookForSale::BookForSale(){}

BookForSale::BookForSale(Book book,int amount)
{
	this->amount = amount;
	this->book = book;
}

Book BookForSale::getBook()
{
	return this->book;
}

int BookForSale::getAmount()
{
	return this->amount;
}


BookForSale::~BookForSale()
{
}


bool BookForSale::equals(BookForSale book)
{
	if (this->book.equals(book.getBook()))
		return true;
	return false;
}
