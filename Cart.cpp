#include "Cart.h"



void Cart::addItem(Book book, int amount ) {
	BookForSale item(book,amount);
	this->items.push_back(item);
}


double Cart::sumUp() {
	double sum = 0;
	for (auto& item : this->items) {
		sum += (item.getAmount() * item.getBook().getPrice());
	}
	return sum;
}

std::vector<BookForSale> Cart::getOrder()
{
	return this->items;
}

Cart::Cart()
{
}


Cart::~Cart()
{
}
