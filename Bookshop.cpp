#include "Bookshop.h"
#include <algorithm>
#include <conio.h>

Bookshop::Bookshop()
{

}


Bookshop::~Bookshop()
{
}


User* Bookshop::signIn()
{
	std::string email, password;
	std::cout << "Введите ваш email" << std::endl;
	std::cin >> email;
	std::cout << "Введите пароль" << std::endl;
	int key = 0;
	bool enter = true;
	while (enter)

	{
		int code = _getch();
		if (code != 8 && code != 13)
		{
			password += code;
			std::cout << '*' << std::flush;
			key++;
		}
		else if (code == 8 && key > 0)
		{
			std::cout << "\b \b" << std::flush;
			password.resize(password.size() - 1);
			key--;
		}
		else if (code == 13)
		{
			enter = false;
		}
	}
	accounts.readAccounts();
	std::vector<User*> accs;
	accs = accounts.getAccounts();
	if (!accs.empty())
	{
		for (auto acc : accs)
		{
			if (acc->getEmail() == email && acc->getPassword() == password)
			{
				if (acc->getUserType() == "admin")
					return new Admin(email, password);
				else if (acc->getUserType() == "buyer")
				{

					return new Buyer(email, password, bank.getPayment(email));
				}
				else
					continue;
			}
		}
	}
	return nullptr;
}

Buyer* Bookshop::signUp()
{
	std::string email,password;
	std::cout << "Enter your email" << std::endl;
	std::cin >> email;
	std::cout << "Enter password" << std::endl;
	int key = 0;
	bool enter = true;
	while (enter)

	{
		int code = _getch();
		if (code != 8 && code != 13)
		{
			password += code;
			std::cout << '*' << std::flush;
			key++;
		}
		else if (code == 8 && key > 0)
		{
			std::cout << "\b \b" << std::flush;
			password.resize(password.size() - 1);
			key--;
		}
		else if (code == 13)
		{
			enter = false;
		}
	}
	accounts.readAccounts();
	std::vector<User*> accs;
	accs = accounts.getAccounts();
	for (auto acc : accs)
	{
		if (acc->getEmail() == email)
		{
			std::cout << "Пользователь с такими данными уже существует" << std::endl;
			return nullptr;
		}
	}
	CreditCard startCard(100);
	Buyer* newBuyer = new Buyer(email, password, startCard);
	accounts.addToUserBase(newBuyer);
	if (!bank.addToBankBase(*newBuyer))
		return nullptr;
	return newBuyer;
}
// проверить и прочистить все векторы


int Bookshop::showAssortment(int mode, Buyer buyer,Cart *cart)
{
	catalog.readCatalog();
	std::vector<BookForSale> items;
	items = catalog.getAssortment();
	if (mode == 1)
		std::sort(items.begin(), items.end(), [](BookForSale book1, BookForSale book2) {return book1.getBook().getName() < book2.getBook().getName(); });
	else if (mode == 2)
		std::sort(items.begin(), items.end(), [](BookForSale book1, BookForSale book2) {return book1.getBook().getAuthor() < book2.getBook().getAuthor(); });
	else if(mode == 3 )
		std::sort(items.begin(), items.end(), [](BookForSale book1, BookForSale book2) {return book1.getBook().getPrice() < book2.getBook().getPrice(); });
	else if (mode == 4)
		std::sort(items.begin(), items.end(), [](BookForSale book1, BookForSale book2) {return book1.getBook().getPrice() > book2.getBook().getPrice(); });
	
	int key=0, code;
	int newMode = 5;
	do
	{
		int i = 0;
		system("cls");
		std::cout << "   |" << std::setw(26) << "       Название       " << "|" << std::setw(26) << "         Автор         " << "|" << std::setw(12) << " Стоимость " <<
			" |" << std::setw(9) << "Кол-во" << "|" << std::endl;
		std::cout << "   |" << "__________________________" << "|" << "__________________________" << "|" << "_____________" << "|" << "_________" << "|" << std::endl;
		for (i; i < items.size();)
		{
			if (i == key)
			{
				std::cout << "-> |" << std::setw(27) << items[i].getBook().getName() + "|" << std::setw(27) << items[i].getBook().getAuthor() + "|" << std::setw(14) <<
					std::to_string(items[i].getBook().getPrice()) + "р|" << std::setw(7) << std::to_string(items[i].getAmount()) << "шт|" << '\n';
			}
			else
				std::cout << "   |" << std::setw(27) << items[i].getBook().getName() + "|" << std::setw(27) << items[i].getBook().getAuthor() + "|" << std::setw(14) <<
				std::to_string(items[i].getBook().getPrice()) + "р|" << std::setw(7) << std::to_string(items[i].getAmount()) << "шт|" << '\n';
			i++;
		}
			std::cout << "   |" << "__________________________" << "|" << "__________________________" << "|" << "_____________" << "|" << "_________" << "|" << std::endl;

			if (key == items.size())
			{
				newMode = 1;
				std::cout << "\t-> По названию книги" << std::endl;
			}
			else
				std::cout << "По названию книги" << std::endl;
			if (key == items.size() + 1)
			{
				newMode = 2;
				std::cout << "\t-> По автору" << std::endl;
			}
			else
				std::cout << "По автору" << std::endl;
			if (key == items.size() + 2)
			{
				newMode = 3;
				std::cout << "\t-> По цене (сначала дешёвые)" << std::endl;
			}
			else
				std::cout << "По цене (сначала дешёвые)" << std::endl;
			if (key == items.size() + 3)
			{
				newMode = 4;
				std::cout << "\t-> По цене (сначала дорогие)" << std::endl;
			}
			else
				std::cout << "По цене (сначала дорогие)" << std::endl;
			code = _getch();
			if (code == 80)
			{
				key++;
				if (key > items.size()+3)
					key = 0;
			}
			if (code == 72)
			{
				key--;
				if (key < 0)
					key = items.size()+3;
			}
			if (code == 13 && key < items.size())
			{
				int amount;
				std::cout << "Введите желаемое кол-во" << std::endl;
				std::cin >> amount;
				if (items[key].getAmount() >= amount)
					addToCart(items[key].getBook(),amount, buyer, cart);
				else
				{
					std::cout << "Введенное кол-во больше доступного на складе" << std::endl;
					system("pause");
				}
			}
			if (code == 13 && key >= items.size())
			{
				catalog.clearAssortment();
				return newMode;
			}
		

	} while (code != 27);
	catalog.clearAssortment();
	return newMode;
}

void Bookshop::buyBooks( Buyer buyer)
{
	if (!carts.empty())
	{
		Cart cart = carts.find(buyer.getEmail())->second;
		if (!cart.getOrder().empty())
		{
			if (enoughMoney(buyer, cart.sumUp()))
			{
				buyer.pay(cart.sumUp()); // снимаются деньги с карты
				catalog.substractOrder(cart.getOrder());
				bank.clearBankData();
				bank.substractBalance(buyer.getEmail(), cart.sumUp());// купленные книги убираются книги со склада
				addToLog(buyer, cart.getOrder());
				cart.getOrder().clear();
				std::cout << "Покупка совершена " << cart.sumUp() << " рублей списано с вашего счёта" << std::endl;
				system("pause");
			}
			else {
				cart.getOrder().clear();
				std::cout << "Недостаточно средств" << std::endl;
				system("pause");
			}
		}
		else
		{
			std::cout << "Корзина пуста" << std::endl;
			system("pause");
		}
	}
	else
	{
		std::cout << "Корзина пуста" << std::endl;
		system("pause");
	}
		
}

bool Bookshop::enoughMoney(Buyer buyer, double totalPurchaseValue)
{
	if (buyer.getPayment().getBalance() >= totalPurchaseValue)
		return true;
	return false;
	
}

void Bookshop::addToCart(Book book, int amount, Buyer buyer, Cart* cart)
{
	this->carts.emplace(buyer.getEmail(), *cart);
	if (catalog.checkAvailability(book, amount))
	{
		cart->addItem(book, amount);
		std::cout << "\"" <<book.getName()<< "\"" << " успешно добавлена в корзину" << std::endl;
		system("pause");
	}
	else
		std::cout << "Невозможно совершить покупку" << std::endl;
}

void Bookshop::showBuyersCart(Buyer buyer)
{

	if (!carts.empty())
	{
		Cart cart = carts.find(buyer.getEmail())->second;
		std::vector<BookForSale> items;
		items = cart.getOrder();
		if (!items.empty())
		{
			double total = 0;
			std::cout << "   |" << std::setw(26) << "       Название       " << "|" << std::setw(26) << "         Автор         " << "|" << std::setw(12) << " Стоимость " <<
				" |" << std::setw(9) << "Кол-во" << "|" << std::endl;
			std::cout << "   |" << "__________________________" << "|" << "__________________________" << "|" << "_____________" << "|" << "_________" << "|" << std::endl;
			for (auto item : items)
			{
				total += (item.getBook().getPrice() * item.getAmount());
				std::cout << "   |" << std::setw(27) << item.getBook().getName() + "|" << std::setw(27) << item.getBook().getAuthor() + "|" << std::setw(14) <<
					std::to_string(item.getBook().getPrice()) + "р|" << std::setw(7) << std::to_string(item.getAmount()) << "шт|" << '\n';
			}
			std::cout << "Итого : " << total << "р"<< std::endl;;
		}
		else
			std::cout << "Корзина пуста" << std::endl;
	}
	else
		std::cout << "Корзина пуста" << std::endl;
}


void Bookshop::addToLog(Buyer buyer, std::vector<BookForSale> order)
{
	
	std::string LOG_FILE = "C:\\Users\\Dima\\source\\repos\\Bookshop\\Log.txt";
	std::fstream add;
	add.open(LOG_FILE.c_str(), std::fstream::out | std::fstream::app);
	for (auto item : order)
	{
		add << buyer.getEmail() <<"|" << item.getBook().getName() << "|"  << item.getAmount() << "|"
			<< item.getBook().getPrice()*item.getAmount()  << '\n';
	}
	add.close();
		
}