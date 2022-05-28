#include "global_transactions.h"


namespace amilib
{
	std::vector<amilib::GlobalFileTransactionsClient*> CreateTransaction::clients = std::vector<amilib::GlobalFileTransactionsClient*>();
	//void amilib::addClient(amilib::TransactionsClient* c)
	//{
	//	amilib::CreateTransaction::clients.push_back(c);
	//}

	std::vector<BooksChangesClient*> CreateTransaction::getBooksChangesClients()
	{
		std::vector<BooksChangesClient*> booksChangesClients;
		for (GlobalFileTransactionsClient* ac : clients)
		{
			BooksChangesClient* bcc = dynamic_cast<BooksChangesClient*>(ac);
			if (bcc != nullptr)
			{
				booksChangesClients.push_back(bcc);
			}
		}
		return booksChangesClients;
	}

	std::vector<UsersChangesClient*> CreateTransaction::getUsersChangesClients()
	{
		std::vector<UsersChangesClient*> booksChangesClients;
		for (GlobalFileTransactionsClient* ac : clients)
		{
			UsersChangesClient* bcc = dynamic_cast<UsersChangesClient*>(ac);
			if (bcc != nullptr)
			{
				booksChangesClients.push_back(bcc);
			}
		}
		return booksChangesClients;
	}

	std::vector<TakeReturnClient*> amilib::CreateTransaction::getTakeReturnClients()
	{
		std::vector<TakeReturnClient*> takeReturnClients;
		for (GlobalFileTransactionsClient* ac : clients)
		{
			TakeReturnClient* trc = dynamic_cast<TakeReturnClient*>(ac);
			if (trc != nullptr)
			{
				takeReturnClients.push_back(trc);
			}
		}
		return takeReturnClients;
	}

	void CreateTransaction::addClient(amilib::GlobalFileTransactionsClient* c)
	{
		CreateTransaction::clients.push_back(c);
	}

	IdCreator::~IdCreator()
	{
	}
	GlobalFileTransactionsClient::GlobalFileTransactionsClient()
	{
	}
	GlobalFileTransactionsClient::~GlobalFileTransactionsClient()
	{
	}
	BooksChangesClient::BooksChangesClient()
	{
	}
	TakeReturnClient::TakeReturnClient()
	{
	}
}
