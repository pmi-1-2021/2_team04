#pragma once

#include "book.h"
#include "account.h"
#include "transactions.h"

#include<unordered_map>




namespace amilib
{
	class BooksLoader : public BooksChangesClient, public TakeReturnClient
	{
	public:
		BooksLoader(std::string info_file_path);
		~BooksLoader();
		void pull(std::unordered_map<int, Book>& books_map);
		//todo
		//void push();
		void addItem(Book b);
		//void deleteItem();
		//
		virtual void changeBookAmmount(int book_id, size_t new_ammount);
		virtual void changeBookInfo(int book_id, Book new_info);
		virtual void addNewBook(Book b);
		virtual void takeBook(int user_id, int book_id);
		virtual void returnBook(int user_id, int book_id);
	private:
		std::string infoFilePath;
	};

	class UsersLoader
	{
	public:
		UsersLoader();
		~UsersLoader();
		//std::unordered_map<int, amilib::Account> users_map;
		void pull(std::unordered_map<int, amilib::Account>& users_map);
		//todo
		//void push();
		void addItem(Account acc);
		//void deleteIte);m(
		//
	};
}
