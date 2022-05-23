#pragma once

#include "account.h"
#include "book.h"
#include "infoLoaders.h"
#include "transactions.h"

#include <vector>
#include <unordered_map>




namespace amilib 
{
	class Menu : virtual public BooksChangesClient, virtual public TakeReturnClient
	{
	public:
		Menu();
		virtual ~Menu();
		void callMain();
		void loadAccInfo();
		void clearInfo();
		virtual void changeBookAmmount(int book_id, size_t new_ammount);
		virtual void changeBookInfo(int book_id, Book new_info);
		virtual void takeBook(int user_id, int book_id);
		virtual void returnBook(int user_id, int book_id);
		virtual void addNewBook(Book b);
	private:
		bool logIn();
		void logOut();
		void signUp();
		void noaccMain();
		void userMain();
		void adminMain();
		void libBookList();
		void userBookList();
		void bookList(std::vector<Book>&);
		void selectBook(Book& book_to_select);
		void drawHeader();
		void bookSearch();
		void takeBook(int id);
		void returnBook(int id);
		void addNewBook();
		bool uniqueNewUsername(std::string name);
		int idAtUsername(std::string name);
		bool askPassword(Account& a);
		std::string createFileName(std::string from);
		Account account;
		BooksLoader booksInfo;
		UsersLoader usersInfo;
		std::unordered_map<int, amilib::Account> usersMap;
		std::unordered_map<int, amilib::Book> booksMap;
	};
}