#pragma once
#ifndef MENU_H
#define MENU_H


#include "account.h"
#include "book.h"
#include "database.h"

#include <vector>
#include <unordered_map>




namespace amilib 
{
	class Library : virtual public BooksChangesClient, virtual public TakeReturnClient
	{
	public:
		Library(BooksDataBase books_data_base, UsersDataBase users_data_base);
		virtual ~Library();
		void callMenu();
		void clearInfo();
		virtual void changeBookAmmount(int book_id, size_t new_ammount);
		virtual void changeBookInfo(int book_id, Book new_info);
		virtual void takeBook(int user_id, int book_id);
		virtual void returnBook(int user_id, int book_id);
		virtual void addNewBook(Book b);
	private:
		Account account;
		BooksDataBase booksDB;
		UsersDataBase usersDB;
		std::unordered_map<int, amilib::Account> usersMap;
		std::unordered_map<int, amilib::Book> booksMap;
		bool logInForm();
		bool askPassword(Account& a);
		void loadAccInfo();
		void logOut();
		void signUpForm();
		void noaccMenu();
		void userMenu();
		void adminMenu();
		void libBookList();
		void userBookList();
		void bookList(std::vector<Book>&);
		void selectBook(Book& book_to_select);
		void transactionTakeBook(int id);
		void transactionReturnBook(int id);
		void newBookForm();
		void editBookForm(Book b);
		int idAtUsernameInMap(std::string name);
		std::string createFileName(std::string from);
		virtual void inputBook(Book b);
		virtual void readBook(Book b);
		virtual size_t getLines(Book b);
		virtual void editBook(Book b);
		void drawHeader();
		//todo:
		void bookSearch();
		//to clear up
		//bool uniqueNewUsername(std::string name);
	};
}
#endif // !MENU_H