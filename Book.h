#pragma once
#include <string>
#include <iostream>
class Book
{
	std::string name;
	std::string author;
	double price;
public:
	std::string getName();
	std::string getAuthor();
	Book();
	Book(std::string name, std::string author,double price);
	double getPrice();
	~Book();
	bool equals(Book book);
};

