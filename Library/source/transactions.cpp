#include "transactions.h"

namespace amilib
{
	amilib::CreateTransactionAddBook::CreateTransactionAddBook(Book new_book)
		: toAdd(new_book)
	{
	}

	amilib::Transaction* amilib::CreateTransactionAddBook::createBy(std::string role)
	{
		std::vector<TransactionsClient*> allClients = std::move(CreateTransaction::getClients());
		std::vector<BooksChangesClient*> booksChangesClients;
		for (TransactionsClient* ac : allClients)
		{
			BooksChangesClient* bcc = dynamic_cast<BooksChangesClient*>(ac);
			if (bcc != nullptr)
			{
				booksChangesClients.push_back(bcc);
			}
		}
		Transaction* t = new TransactionAddBook(toAdd, booksChangesClients);
		return t;
	}

	CreateTransactionChangeBookAmmount::CreateTransactionChangeBookAmmount(int book_id, size_t new_ammount)
		:id(book_id),
		ammount(new_ammount)
	{
	}
	Transaction* CreateTransactionChangeBookAmmount::createBy(std::string role)
	{
		std::vector<TransactionsClient*> allClients = std::move(CreateTransaction::getClients());
		std::vector<BooksChangesClient*> booksChangesClients;
		for (TransactionsClient* ac : allClients)
		{
			BooksChangesClient* bcc = dynamic_cast<BooksChangesClient*>(ac);
			if (bcc != nullptr)
			{
				booksChangesClients.push_back(bcc);
			}
		}
		Transaction* t = new TransactionChangeBookAmmount(id, ammount, booksChangesClients);
		return t;
	}

	std::vector<amilib::TransactionsClient*> amilib::CreateTransaction::getClients()
	{
		return std::vector<TransactionsClient*>(clients);
	}

	amilib::TransactionsClient::~TransactionsClient()
	{
	}

	amilib::TransactionAddBook::TransactionAddBook(Book new_book, std::vector<BooksChangesClient*> bccVec)
		:book(new_book),
		booksChangesClients(bccVec)
	{
	}

	void amilib::TransactionAddBook::execute()
	{
		for (BooksChangesClient* c : this->booksChangesClients)
		{
			c->addNewBook(this->book);
		}
	}

	std::vector<TransactionsClient*> CreateTransaction::clients = std::vector<TransactionsClient*>();

	TransactionChangeBookAmmount::TransactionChangeBookAmmount(int book_id, size_t new_ammount, std::vector<BooksChangesClient*> bccVec)
		:id(book_id),
		ammount(new_ammount),
		booksChangesClients(bccVec)
	{
	}
	void TransactionChangeBookAmmount::execute()
	{
		for (BooksChangesClient* c : this->booksChangesClients)
		{
			c->changeBookAmmount(this->id, this->ammount);
		}
	}
	CreateTransactionTakeBook::CreateTransactionTakeBook(int user_id, int book_id)
		: userId(user_id),
		bookId(book_id)
	{
	}
	Transaction* CreateTransactionTakeBook::createBy(std::string role)
	{
		std::vector<TransactionsClient*> allClients = std::move(CreateTransaction::getClients());
		std::vector<TakeReturnClient*> takeReturnClients;
		for (TransactionsClient* ac : allClients)
		{
			TakeReturnClient* trc = dynamic_cast<TakeReturnClient*>(ac);
			if (trc != nullptr)
			{
				takeReturnClients.push_back(trc);
			}
		}
		Transaction* t = new TransactionTakeBook(userId, bookId, takeReturnClients);
		return t;
	}
	CreateTransactionReturnBook::CreateTransactionReturnBook(int user_id, int book_id)
		: userId(user_id),
		bookId(book_id)
	{
	}
	Transaction* CreateTransactionReturnBook::createBy(std::string role)
	{
		std::vector<TransactionsClient*> allClients = std::move(CreateTransaction::getClients());
		std::vector<TakeReturnClient*> takeReturnClients;
		for (TransactionsClient* ac : allClients)
		{
			TakeReturnClient* trc = dynamic_cast<TakeReturnClient*>(ac);
			if (trc != nullptr)
			{
				takeReturnClients.push_back(trc);
			}
		}
		Transaction* t = new TransactionReturnBook(userId, bookId, takeReturnClients);
		return t;
	}
	TransactionTakeBook::TransactionTakeBook(int user_id, int book_id, std::vector<TakeReturnClient*> trcVec)
		: userId(user_id),
		bookId(book_id),
		takeReturnClients(trcVec)
	{
	}
	void TransactionTakeBook::execute()
	{
		for (TakeReturnClient* c : this->takeReturnClients)
		{
			c->takeBook(this->userId, this->bookId);
		}
	}
	TransactionReturnBook::TransactionReturnBook(int user_id, int book_id, std::vector<TakeReturnClient*> trcVec)
		: userId(user_id),
		bookId(book_id),
		takeReturnClients(trcVec)
	{
	}
	void TransactionReturnBook::execute()
	{
		for (TakeReturnClient* c : this->takeReturnClients)
		{
			c->returnBook(this->userId, this->bookId);
		}
	}
}


