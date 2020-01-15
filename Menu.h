#pragma once
#include "Bookshop.h"
#include "ValidData.h"
class Menu
{
	int manageInputAdminMenu();
	int manageInputBuyerMenu();
public:
	void buyerMode(Buyer* buyer,Bookshop* shop);
	void adminMode(Admin* admin);
	
	Menu();
	~Menu();
};

