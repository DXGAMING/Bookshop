#pragma once
#include <conio.h>
template <class T>
class ValidData
{
public:
	static T getValidValue(std::string messageOfError)
	{
		T value;
		std::cin >> value;
		while (std::cin.fail() || std::cin.get() != '\n')
		{
			std::cout << messageOfError;

			std::cin.clear();

			rewind(stdin);

			std::cin >> value;

		}
		return value;

	}
	/*static int manageInput(std::vector<BookForSale> vector)
	{
		do {
			
		}while(code !=13)
	}*/
	ValidData();
	~ValidData();
};	