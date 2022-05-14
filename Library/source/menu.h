#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include "book.h"
#include "infoLoaders.h"
#include "user.h"

namespace amilib
{
	class IMenu
	{
	protected:
		BooksLoader m_books;
	public:
		virtual char callMain() = 0;
		virtual char libList(std::vector<std::unordered_map<std::string, Book>::iterator> _available_books) = 0;
		virtual char selectBook(Book& _selected_book) = 0;
		virtual void drawHeader() = 0;
		virtual void drawMain() = 0;
		//virtual void drawBookList(std::map<std::string, std::set<Book>>& _books) = 0; 
		virtual void drawExternals() = 0;
		//virtual void drawSelectBook() = 0;
		virtual void bookSearch() = 0;
		
	private:

	};

	class StartMenu : public IMenu
	{
	public:

		virtual char callMain();
		virtual char libList(std::vector<std::unordered_map<std::string, Book>::iterator> _available_books);
		virtual char selectBook(Book& _selected_book);
		virtual void drawHeader();
		virtual void drawMain();
		//virtual void drawBookList(std::map<std::string, std::set<Book>>& _books);
		virtual void drawExternals();
		//virtual void drawSelectBook();
		virtual void bookSearch();
	};

	class MenuLogged : public IMenu
	{
		IMenu* m_start_menu;
	public:
		virtual char callMain() = 0;
		virtual char libList(std::vector<std::unordered_map<std::string, Book>::iterator> _available_books);
		virtual void callAccMenu();
		virtual char selectBook(Book& _selected_book);
		virtual void drawHeader();
		virtual void drawMain();
		//virtual void drawBookList(std::map<std::string, std::set<Book>>& _books);
		virtual void drawAccMenu();
		virtual void drawExternals();
		//virtual void drawSelectBook();
		virtual void bookSearch();
		virtual void takeBook();
		virtual void returnBook();
	protected:
		Account m_acc;
	};

	class UserMenu : public MenuLogged
	{
	public:

	};

	class AdminMenu : public MenuLogged
	{
	public:

	};
}