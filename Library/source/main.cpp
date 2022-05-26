#include "menu.h"
#include "idcreator.h"
#include "user_transactions.h"
#include "book_transactions.h"
#include "bookstaking.h"


#include <vector>


//void amilib::addClient(amilib::TransactionsClient* c)
//{
//	amilib::CreateTransaction::clients.push_back(c);
//}


int main()
{
	amilib::BooksDataBase* booksBase = new amilib::BooksDataBase("..\\BusinessData\\booksInfo.txt");
	amilib::UsersDataBase* usersBase = new amilib::UsersDataBase("..\\BusinessData\\users.txt");

	amilib::IdCreator* bookIdCreator = new amilib::BooksDataBase("..\\BusinessData\\booksInfo.txt");
	amilib::IdCreator* userIdCreator = new amilib::UsersDataBase("..\\BusinessData\\users.txt");

	amilib::AddBookTransaction::ids = bookIdCreator;
	amilib::AddUserTransaction::ids = userIdCreator;

	amilib::TransactionsClient* booksBaseTclient = new amilib::BooksDataBase("..\\BusinessData\\booksInfo.txt");
	amilib::TransactionsClient* usersBaseTclient = new amilib::UsersDataBase("..\\BusinessData\\users.txt");
	amilib::TransactionsClient* takeReturnBaseTclient = new amilib::BooksTakingBase("..\\BusinessData\\takings.txt");

	std::vector<amilib::TransactionsClient*> transactionClients;
	transactionClients.push_back(takeReturnBaseTclient);
	transactionClients.push_back(booksBaseTclient);
	transactionClients.push_back(usersBaseTclient);
	amilib::CreateTransaction::clients = transactionClients;

	amilib::TransactionsClient* m = new amilib::Menu(*booksBase, *usersBase);
	amilib::CreateTransaction::addClient(m);

	amilib::Menu* menu = dynamic_cast<amilib::Menu*>(m);
	menu->callMain();
	return 0;
}