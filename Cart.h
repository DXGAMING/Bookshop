#pragma once
#include "BookForSale.h"
#include <vector>
class Cart
{
	std::vector<BookForSale> items;
public:
	void addItem(Book book, int amount);
	double sumUp();
	std::vector<BookForSale> getOrder();
	Cart();
	~Cart();
};

