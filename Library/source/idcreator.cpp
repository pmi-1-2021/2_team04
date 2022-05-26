#include "idcreator.h"


namespace amilib
{
	std::vector<amilib::TransactionsClient*> CreateTransaction::clients = std::vector<amilib::TransactionsClient*>();
	//void amilib::addClient(amilib::TransactionsClient* c)
	//{
	//	amilib::CreateTransaction::clients.push_back(c);
	//}

	std::vector<BooksChangesClient*>&& CreateTransaction::getBooksChangesClients()
	{
		std::vector<BooksChangesClient*> booksChangesClients;
		for (TransactionsClient* ac : clients)
		{
			BooksChangesClient* bcc = dynamic_cast<BooksChangesClient*>(ac);
			if (bcc != nullptr)
			{
				booksChangesClients.push_back(bcc);
			}
		}
		return std::move(booksChangesClients);
	}

	std::vector<UsersChangesClient*>&& CreateTransaction::getUsersChangesClients()
	{
		std::vector<UsersChangesClient*> booksChangesClients;
		for (TransactionsClient* ac : clients)
		{
			UsersChangesClient* bcc = dynamic_cast<UsersChangesClient*>(ac);
			if (bcc != nullptr)
			{
				booksChangesClients.push_back(bcc);
			}
		}
		return std::move(booksChangesClients);
	}

	std::vector<TakeReturnClient*>&& amilib::CreateTransaction::getTakeReturnClients()
	{
		std::vector<TakeReturnClient*> takeReturnClients;
		for (TransactionsClient* ac : clients)
		{
			TakeReturnClient* trc = dynamic_cast<TakeReturnClient*>(ac);
			if (trc != nullptr)
			{
				takeReturnClients.push_back(trc);
			}
		}
		return std::move(takeReturnClients);
	}

	void CreateTransaction::addClient(amilib::TransactionsClient* c)
	{
		CreateTransaction::clients.push_back(c);
	}

	IdCreator::~IdCreator()
	{
	}
	TransactionsClient::TransactionsClient()
	{
	}
	TransactionsClient::~TransactionsClient()
	{
	}
	BooksChangesClient::BooksChangesClient()
	{
	}
	TakeReturnClient::TakeReturnClient()
	{
	}
}
