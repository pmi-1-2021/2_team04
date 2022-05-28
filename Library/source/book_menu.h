#pragma once
#ifndef BOOK_MENU_H
#define BOOK_MENU_H

#include "account.h"
#include "book.h"

namespace amilib
{
	class BookMenu
	{
	public:
		BookMenu(Book b, std::string user_role, bool book_is_taken);
		~BookMenu();
		void draw();
		char getAction();
		bool exitKey();
		void setIsBookTaken(bool is_taken);
	private:
		bool exit;
		Book selected;
		std::string userRole;
		bool isTaken;
		void drawInfo();
		void drawContolPanel();
	};
}

#endif // !BOOK_MENU_H
