#include "Book.h"



Book::Book(){

}
std::string Book:: getName() {
	return name;
}


std::string Book:: getAuthor() {
	return author;
}



Book::Book(std::string name, std::string author,double price) {
	this->name = name;
	this->author = author;
	this->price = price;

}



double Book::getPrice(){
	return price;
}

Book::~Book()
{
}
bool Book::equals(Book book) {
	if (book.getName() == name && book.getAuthor() == author)
		return true;
	return false;

}