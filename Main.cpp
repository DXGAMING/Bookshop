
#include "Menu.h"
 int manageInputMain()
{
	int key = 1, code;
	do {
		system("cls");
		std::cout << "\t\t     |    Войдите или Зарегистрируйтесь    |       " << std::endl;
		if (key == 1)
			std::cout << "\t-> Вход" << std::endl;
		else
			std::cout << "\tВход" << std::endl;
		if (key == 2)
			std::cout << "\t-> Регистрация" << std::endl;
		else
			std::cout << "\tРегистрация" << std::endl;
		if (key == 3)
			std::cout << "\t-> Выход" << std::endl;
		else
			std::cout << "\tВыход" << std::endl;
		code = _getch();
		if (code == 80)
		{
			key++;
			if (key > 3)
				key = 1;
		}
		if (code == 72)
		{
			key--;
			if (key < 1)
				key = 3;
		}
	} while (code != 13);
	return key;
}
int main() {
	setlocale(LC_ALL, "ru");
	
	int mainMenuNum = 0;
	Bookshop* shop = new Bookshop();
	Menu menu;
	while (true)
	{
		mainMenuNum = manageInputMain();
		switch (mainMenuNum)
		{
		case 1:
		{
			User* startUser = shop->signIn();
			if (startUser != nullptr)
			{
				if (typeid(*startUser).name() == typeid(Admin).name())
				{

					menu.adminMode(dynamic_cast<Admin*>(startUser));
				}
				else if (typeid(*startUser).name() == typeid(Buyer).name())
				{
					menu.buyerMode(dynamic_cast<Buyer*>(startUser), shop);
				}
			}
			else
			{
				system("cls");
				std::cout << "Попробуйте снова" << std::endl;
				break;
			}
			break; 
		}
		case 2:
		{
			User* startUser = shop->signUp();
			if (startUser != nullptr)
				menu.buyerMode(dynamic_cast<Buyer*>(startUser), shop);

			// работаем  только как с покупателем
			break;
		}
		case 3:
			delete shop;
			exit(0);
		default:
			break;
		}
	}
}

