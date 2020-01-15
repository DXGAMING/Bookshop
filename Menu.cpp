#include "Menu.h"
#include "Windows.h"


void Menu::buyerMode(Buyer* b, Bookshop* shop)
{
	system("cls");
	Buyer buyer = *b;
	int buyerNum = 0;

	std::string author, name;
	double price;
	int amount;
	bool existence = false, largerAmount = false;;
	std::vector<BookForSale> assortment;
	Catalog* catalog  = new Catalog();
	Cart* cart = new Cart();
	while (true)
	{

		
		
	
		buyerNum = manageInputBuyerMenu();
		switch (buyerNum)
		{
		case 1: 
		{
			system("cls");
			int mode = 0;
			while(mode!=5)
				mode = shop->showAssortment(mode , *b, cart);
			break;
		}
		case 2:
			system("cls");
			b->findBook();
			break;
		case 3:
			system("cls");
			shop->showBuyersCart(buyer);
			system("pause");
			break;
		case 4:
			shop->buyBooks(buyer);
			break;
		case 5:
			system("cls");
			return;
		default:
			break;
		}
	}

}

void Menu::adminMode(Admin* admin)
{
	system("cls");
	int adminNum;
		while (true)
		{
			adminNum = manageInputAdminMenu();
			switch (adminNum)
			{
			case 1:
			
				admin->findBook();
				break;
			case 2:
				system("cls");
				admin->addBook();
				break;
			case 3:
				system("cls");
				admin->deleteBook();
				break;
			case 5:
				system("cls");
				admin->showInput();
				break;
			case 4:
				system("cls");
				admin->readLog();
				break;
			case 6:
				system("cls");
				return;			
			default:
				break;
			
			}
		}
}

int Menu::manageInputAdminMenu()
{
	int key = 1, code;
	do {
		system("cls");
		std::cout << "\n\t\t     |     Администрирование     |     " << std::endl;
		if (key == 1)
			std::cout << "\t-> Найти позицию по символам" << std::endl;
		else
			std::cout << "\tНайти позицию по символам" << std::endl;
		if (key == 2)
			std::cout << "\t-> Добавить новую позицию или увеличить количество существующей" << std::endl;
		else
			std::cout << "\tДобавить новую позицию или увеличить количество существующей" << std::endl;
		if (key == 3)
			std::cout << "\t-> Удалить существующую позицию" << std::endl;
		else
			std::cout << "\tУдалить существующую позицию" << std::endl;
		if(key == 4)
			std::cout << "\t-> Вывести топ продаваемых книг" << std::endl;
		else
			std::cout << "\tВывести топ продаваемых книг" << std::endl;
		if (key == 5)
			std::cout << "\t-> Вывести общую выручку" << std::endl;
		else
			std::cout << "\tВывести общую выручку" << std::endl;
		if(key == 6)
			std::cout << "\t-> В главное меню" << std::endl;
		else
			std::cout << "\tВ главное меню" << std::endl;
		code = _getch();
		if (code == 80)
		{
			key++;
			if (key > 6)
				key = 1;
		}
		if (code == 72)
		{
			key--;
			if (key < 1)
				key = 6;
		}
	} while (code != 13);
	return key;
}

int Menu::manageInputBuyerMenu()
{
	int key = 1, code;
	do {
		system("cls");
		std::cout << "\n\t\t      |     Книжный магазин     |     " << std::endl;
		if (key == 1)
			std::cout << "\t-> Показать каталог" << std::endl;
		else
			std::cout << "\tПоказать каталог" << std::endl;
		if (key == 2)
			std::cout << "\t-> Найти книгу" << std::endl;
		else
			std::cout << "\tНайти книгу" << std::endl;
		if (key == 3)
			std::cout << "\t-> Просмотреть корзину" << std::endl;
		else
			std::cout << "\tПросмотреть корзину" << std::endl;
		if(key == 4)
			std::cout << "\t-> Оформить покупку" << std::endl;
		else
			std::cout << "\tОформить покупку" << std::endl;
		if (key == 5)
			std::cout << "\t-> В главное меню" << std::endl;
		else
			std::cout << "\tВ главное меню" << std::endl;
		code = _getch();
		if (code == 80)
		{
			key++;
			if (key > 5)
				key = 1;
		}
		if (code == 72)
		{
			key--;
			if (key < 1)
				key = 5;
		}
	} while (code != 13);
	return key;
}


Menu::Menu()
{
}


Menu::~Menu()
{
}
