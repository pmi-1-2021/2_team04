#include "menu.h"
#include "global_transactions.h"
#include "user_transactions.h"
#include "book_transactions.h"
#include "bookstaking.h"


#include <vector>



int main()
{
	amilib::BooksDataBase* booksBase = new amilib::BooksDataBase("..\\BusinessData\\booksInfo.txt");
	amilib::UsersDataBase* usersBase = new amilib::UsersDataBase("..\\BusinessData\\users.txt");

	amilib::IdCreator* bookIdCreator = new amilib::BooksDataBase("..\\BusinessData\\booksInfo.txt");
	amilib::IdCreator* userIdCreator = new amilib::UsersDataBase("..\\BusinessData\\users.txt");

	amilib::AddBookTransaction::ids = bookIdCreator;
	amilib::AddUserTransaction::ids = userIdCreator;

	amilib::GlobalFileTransactionsClient* booksBaseTclient = new amilib::BooksDataBase("..\\BusinessData\\booksInfo.txt");
	amilib::GlobalFileTransactionsClient* usersBaseTclient = new amilib::UsersDataBase("..\\BusinessData\\users.txt");
	amilib::GlobalFileTransactionsClient* takeReturnBaseTclient = new amilib::BooksTakingBase("..\\BusinessData\\takings.txt");

	std::vector<amilib::GlobalFileTransactionsClient*> transactionClients;
	transactionClients.push_back(takeReturnBaseTclient);
	transactionClients.push_back(booksBaseTclient);
	transactionClients.push_back(usersBaseTclient);
	amilib::CreateTransaction::clients = transactionClients;

	amilib::GlobalFileTransactionsClient* m = new amilib::Library(*booksBase, *usersBase);
	amilib::CreateTransaction::addClient(m);

	amilib::Library* menu = dynamic_cast<amilib::Library*>(m);
	menu->callMenu();
	return 0;
}