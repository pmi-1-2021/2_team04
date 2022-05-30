#include "book_menu.h"

#include <iostream>

amilib::BookMenu::BookMenu(Book b, std::string user_role, bool book_is_taken)
	:exit(false),
	selected(b),
	userRole(user_role),
	isTaken(book_is_taken)
{
}

amilib::BookMenu::~BookMenu()
{
}

char amilib::BookMenu::getAction()
{
	char ch = ' ';
	do
	{
		std::cin >> ch;
		if (isTaken && ch == 'r')
		{
			return 'r';
		}
		else if (isTaken && ch == 'b')
		{
			return 'b';
		}
		else if (!isTaken && ch == 't')
		{
			return 't';
		}
		if (this->userRole == "admin" && ch == 'e')
		{
			return 'e';
		}
		else if (this->userRole == "admin" && ch == 'a')
		{
			return 'a';
		}
	}
	while (ch != 'x');
	exit = true;
}

void amilib::BookMenu::draw()
{
	system("CLS");
	drawInfo();
	drawContolPanel();
}

void amilib::BookMenu::drawInfo()
{
	std::cout << "Title\t" << this->selected.getTitle() << "\n";
	std::cout << "Author\t" << this->selected.getAuthor() << "\n";
	std::cout << "Pages\t" << this->selected.getSize() << "\n";
}

void amilib::BookMenu::drawContolPanel()
{
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	if (this->isTaken)
	{
		std::cout << "[r] read book\n[b] return the book\n";
	}
	else
	{
		std::cout << "[t] take book\n";
	}
	if (this->userRole == "admin")
	{
		std::cout << "[e] edit book info\n[a] add book's text\n";
	}
	std::cout << "[x] return back\n";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	std::cout << "\n > ";
}

bool amilib::BookMenu::exitKey()
{
	return this->exit;
}

void amilib::BookMenu::setIsBookTaken(bool is_taken)
{
	this->isTaken = is_taken;
}
