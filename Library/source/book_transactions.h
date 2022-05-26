#pragma once
#ifndef BOOK_TRANSACTIONS_H
#define BOOK_TRANSACTIONS_H




#include "book.h"
#include "idcreator.h"

#include <string>
#include <vector>


namespace amilib
{
	class AddBookTransaction : public Transaction
	{
	public:
		AddBookTransaction(int by_id, amilib::Book new_book, std::vector<BooksChangesClient*>);
		virtual void execute();
		//todo : private:
		static IdCreator* ids;
	private:
		int byId;
		Book newBook;
		std::vector<BooksChangesClient*> booksChangesClients;
	};

	class CreateAddBookTransaction : public CreateTransaction
	{
	public:
		CreateAddBookTransaction(Book new_book);
		virtual Transaction* createBy(int id);
	private:
		Book toAdd;
	};

	class ChangeBookInfoTransaction : public Transaction
	{
	public:
		ChangeBookInfoTransaction(int by_id, int book_id, Book for_book, std::vector<BooksChangesClient*>);
		virtual void execute();
	private:
		int byId;
		int bookId;
		Book toChange;
		std::vector<BooksChangesClient*> booksChangesClients;
	};

	class CreateChangeBookInfoTransaction : public CreateTransaction
	{
	public:
		CreateChangeBookInfoTransaction(int book_id, Book for_book);
		virtual Transaction* createBy(int id);
	private:
		int bookId;
		amilib::Book changedBook;
	};

	class TakeBookTransaction : public Transaction
	{
	public:
		TakeBookTransaction(int user_id, int book_id, std::vector<TakeReturnClient*>);
		virtual void execute();
	private:
		int userId;
		int bookId;
		std::vector<TakeReturnClient*> takeReturnClients;
	};

	class CreateTakeBookTransaction : public CreateTransaction
	{
	public:
		CreateTakeBookTransaction(int book_id);
		virtual Transaction* createBy(int id);
	private:
		int bookId;
	};

	class ReturnBookTransaction : public Transaction
	{
	public:
		ReturnBookTransaction(int user_id, int book_id, std::vector<TakeReturnClient*>);
		virtual void execute();
	private:
		int userId;
		int bookId;
		std::vector<TakeReturnClient*> takeReturnClients;
	};

	class CreateReturnBookTransaction : public CreateTransaction
	{
	public:
		CreateReturnBookTransaction(int book_id);
		virtual Transaction* createBy(int id);
	private:
		int bookId;
	};
}

#endif // !BOOK_TRANSACTIONS_H