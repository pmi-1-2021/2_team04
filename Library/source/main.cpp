#include "menu.h"
#include "transactions.h"
#include "bookstaking.h"


void amilib::addClient(amilib::TransactionsClient* c)
{
	amilib::CreateTransaction::clients.push_back(c);
}

int main()
{
	amilib::TransactionsClient* takeReturn = new amilib::BooksTaking("..\\BusinessData\\takings.txt");
	amilib::TransactionsClient* booksInfo = new amilib::BooksLoader ("..\\BusinessData\\booksInfo.txt");
	amilib::UsersLoader usersInfo;
	amilib::TransactionsClient* m = new amilib::Menu;
	addClient(takeReturn);
	addClient(booksInfo);
	addClient(m);
	amilib::Menu* menu = dynamic_cast<amilib::Menu*>(m);
	menu->callMain();
	return 0;
}