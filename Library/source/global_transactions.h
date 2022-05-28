#pragma once
#ifndef GLOBAL_TRANSACTIONS_H
#define GLOBAL_TRANSACTIONS_H

#include "account.h"
#include "book.h"


namespace amilib
{
	class GlobalFileTransactionsClient
	{
	public:
		GlobalFileTransactionsClient();
		virtual ~GlobalFileTransactionsClient();
	};

	class TakeReturnClient : virtual public GlobalFileTransactionsClient
	{
	public:
		TakeReturnClient();
		virtual void takeBook(int user_id, int book_id) = 0;
		virtual void returnBook(int user_id, int book_id) = 0;
	};

	class UsersChangesClient : virtual public GlobalFileTransactionsClient
	{
	public:
		virtual void changeUserInfo(int user_id, Account new_info) = 0;
		virtual void addNewUser(Account a) = 0;
	};

	class BooksChangesClient : virtual public GlobalFileTransactionsClient
	{
	public:
		BooksChangesClient();
		virtual void changeBookAmmount(int book_id, size_t new_ammount) = 0;
		virtual void changeBookInfo(int book_id, Book changes) = 0;
		virtual void addNewBook(Book b) = 0;
	};

	class GlobalFileTransaction
	{
	public:
		//virtual ~Transaction();
		virtual void execute() = 0;
	};

	class CreateTransaction
	{
	public:
		virtual GlobalFileTransaction* createBy(int id) = 0;
		std::vector<BooksChangesClient*> getBooksChangesClients();
		std::vector<UsersChangesClient*> getUsersChangesClients();
		std::vector<TakeReturnClient*> getTakeReturnClients();
		static void addClient(amilib::GlobalFileTransactionsClient* c);
		static std::vector<GlobalFileTransactionsClient*> clients;
	private:
	};

	class IdCreator
	{
	public:
		virtual int createId() = 0;
		virtual ~IdCreator();
	};
}
#endif // !GLOBAL_TRANSACTIONS_H