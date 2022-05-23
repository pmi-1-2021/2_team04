#pragma once

#include "book.h"
#include "account.h"

#include <string>


namespace amilib
{

	class Transaction;
	class TransactionAddBook;

	class TransactionsClient
	{
	public:
		virtual ~TransactionsClient();
	};

	class TakeReturnClient : virtual public TransactionsClient
	{
	public:
		virtual void takeBook(int user_id, int book_id) = 0;
		virtual void returnBook(int user_id, int book_id) = 0;
	};

	class UsersChangesClient : virtual public TransactionsClient
	{
	public:
		virtual void changeUserInfo(int user_id, Account new_info) = 0;
		virtual void addNewUser(Account a) = 0;
	};

	class BooksChangesClient : virtual public TransactionsClient
	{
	public:
		virtual void changeBookAmmount(int book_id, size_t new_ammount) = 0;
		virtual void changeBookInfo(int book_id, Book new_info) = 0;
		virtual void addNewBook(Book b) = 0;
	};

	class CreateTransaction
	{
	public:
		virtual Transaction* createBy(std::string role) = 0;
		std::vector<TransactionsClient*> getClients();
		friend void addClient(amilib::TransactionsClient* c);
	private:
		static std::vector<TransactionsClient*> clients;
	};

	class CreateTransactionAddBook : public CreateTransaction
	{
	public:
		CreateTransactionAddBook(Book new_book);
		virtual Transaction* createBy(std::string role);
	private:
		Book toAdd;
	};

	class CreateTransactionChangeBookAmmount : public CreateTransaction
	{
	public:
		CreateTransactionChangeBookAmmount(int book_id, size_t new_ammount);
		virtual Transaction* createBy(std::string role);
	private:
		int id;
		size_t ammount;
	};

	class CreateTransactionTakeBook : public CreateTransaction
	{
	public:
		CreateTransactionTakeBook(int user_id, int book_id);
		virtual Transaction* createBy(std::string role);
	private:
		int userId;
		int bookId;
	};

	class CreateTransactionReturnBook : public CreateTransaction
	{
	public:
		CreateTransactionReturnBook(int user_id, int book_id);
		virtual Transaction* createBy(std::string role);
	private:
		int userId;
		int bookId;
	};

	class Transaction
	{
	public:
		virtual void execute() = 0;
	};

	class TransactionAddBook : public Transaction
	{
	public:
		TransactionAddBook(Book new_book, std::vector<BooksChangesClient*>);
		virtual void execute();
	private:
		Book book;
		std::vector<BooksChangesClient*> booksChangesClients;
	};

	class TransactionChangeBookAmmount : public Transaction
	{
	public:
		TransactionChangeBookAmmount(int book_id, size_t new_ammount, std::vector<BooksChangesClient*>);
		virtual void execute();
	private:
		int id;
		size_t ammount;
		std::vector<BooksChangesClient*> booksChangesClients;
	};

	class TransactionTakeBook : public Transaction
	{
	public:
		TransactionTakeBook(int user_id, int book_id, std::vector<TakeReturnClient*>);
		virtual void execute();
	private:
		int userId;
		int bookId;
		std::vector<TakeReturnClient*> takeReturnClients;
	};

	class TransactionReturnBook : public Transaction
	{
	public:
		TransactionReturnBook(int user_id, int book_id, std::vector<TakeReturnClient*>);
		virtual void execute();
	private:
		int userId;
		int bookId;
		std::vector<TakeReturnClient*> takeReturnClients;
	};

}