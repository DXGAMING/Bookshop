#pragma once
#include "Book.h"
class BookForSale
{
	Book book;
	int amount;
public:
	BookForSale();
	BookForSale(Book book,int amount);
	Book getBook();
	int getAmount();
	~BookForSale();
	bool equals(BookForSale book4sale);
};

