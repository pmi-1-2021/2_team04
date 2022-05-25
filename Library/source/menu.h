#pragma once

#include "book.h"
#include "infoLoaders.h"
#include "account.h"

#include <vector>
#include <unordered_map>




namespace amilib
{
	class Menu
	{
	public:
		Menu();
		~Menu();
		void callMain();
		void loadAccInfo();
		void clearInfo();
	private:
		bool logIn();
		void logOut();
		void signUp();
		void noaccMain();
		void userMain();
		void adminMain();
		void libBookList();
		void userBookList();
		void bookList(std::vector<std::unordered_map<int, Book>::iterator> &available_books);
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