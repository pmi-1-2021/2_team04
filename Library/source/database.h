#pragma once
#ifndef INFO_LOADERS_H
#define INFO_LOADERS_H


#include "book.h"
#include "account.h"
#include "book_transactions.h"
#include "user_transactions.h"

#include<unordered_map>




namespace amilib
{
	class BooksDataBase : virtual public BooksChangesClient, virtual public TakeReturnClient, public IdCreator
	{
	public:
		BooksDataBase(std::string info_file_path);
		~BooksDataBase();
		void pull(std::unordered_map<int, Book>& books_map);
		virtual void changeBookAmmount(int book_id, size_t new_ammount);
		virtual void changeBookInfo(int book_id, Book changes);
		virtual void addNewBook(Book b);
		virtual void takeBook(int user_id, int book_id);
		virtual void returnBook(int user_id, int book_id);
		virtual int createId();
	private:
		std::string infoFilePath;
	};

	class UsersDataBase : public UsersChangesClient, public IdCreator
	{
	public:
		UsersDataBase(std::string info_file_path);
		~UsersDataBase();
		virtual void changeUserInfo(int user_id, Account new_info);
		virtual void addNewUser(Account a);
		virtual int createId();
		void pull(std::unordered_map<int, amilib::Account>& users_map);
		bool isExist(std::string username);
	private:
		std::string infoFilePath;
	};
}
#endif // !INFO_LOADERS_H
