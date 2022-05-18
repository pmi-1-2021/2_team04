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
		void logIn();
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
		void updateUsers();
		void updateBooks();
		void takeBook(int id);
		void returnBook(int id);
		Account account;
		BooksLoader books;
		UsersLoader users;
	};
}