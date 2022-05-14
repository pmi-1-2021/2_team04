#include "menu.h"


namespace amilib
{
	enum StartActions
	{
		libbooklist, findbook
	};

	char StartMenu::callMain()
	{
		char ch;
		while (std::cin.get(ch))
		{
			if (ch == 'l')
			{
				/*char ch1 = */libList(m_books.m_available_books_itervec);
				//if ch1 == l, redraw main
				//
			}
			else if (ch == 's')
			{
				bookSearch();
			}
			else
			{
				return ch;
			}
		}
		return '0';
	}

	char StartMenu::libList(std::vector<std::unordered_map<std::string, Book>::iterator> _books_itervec)
	{
		std::cout << "Enter\n[x] to return back\n[n] to select Book with number 'n'\n\n";
		std::cout << "Title\t\t\tAuthor" << std::endl;
		std::cout << "----------------------------------------------------------------------------" << std::endl;
		for (size_t i = 0; i < _books_itervec.size(); i++)
		{
			std::cout << "[" << i << "] " << _books_itervec[i]->second.get_title() << "\t\t\t" << _books_itervec[i]->second.get_author() << std::endl;
		}
		std::cout << "Enter\n[x] to return back\n[n] to select Book with number 'n'\n\n";
		std::cout << "> ";
		std::string userstr;
		std::cin >> userstr;
		if (userstr.size() == 1)
		{
			return userstr[0];
		}
		int n = 0; 
		//todo: convert userstr to int
		//if converted to int - select *_books_itervec[n]
		//else 		std::cout << "> "; 		std::cin >> userstr;
	}

	char StartMenu::selectBook(Book& _selected_book)
	{
		std::string available;
		if (_selected_book.get_availability())
		{
			available = "[Available]";
		}
		else
		{
			available = "[Not available]";
		}
		std::cout << available << std::endl;
		std::cout << _selected_book.get_title() << "\t\t\t" << _selected_book.get_author() << std::endl;
		std::cout << "Number of pages:" << _selected_book.get_size() << std::endl << std::endl;
		std::cout << "Enter [x] to return back\n\n";
		std::cout << "> ";
		//return cin >> char
		return '0';
	}

	void StartMenu::drawHeader()
	{
		std::cout << "Amilib by AMi-11" << std::endl;
		std::cout << "================================================================" << std::endl;
		std::cout << "Log in to start reading with Amilib" << std::endl;
		std::cout << "================================================================" << std::endl << std::endl;
	}

	void StartMenu::drawExternals()
	{
		std::cout << "[i] log in\n[u] sign up \n\n";
	}

	void amilib::StartMenu::drawMain()
	{
		std::cout << "[l] available books \n[s] search for book\n\n";
	}

	void StartMenu::bookSearch()
	{
		std::string title = " ";
		while (title != "x")
		{
			std::cout << "Enter full title of book\n> ";
			std::cout << "Enter [x] to return back\n\n";
			std::cout << "> ";
			std::cin >> title;
			auto titleRange = m_books.m_books_map.equal_range(title);
			if (titleRange.first == titleRange.second)
			{
				std::cout << "Book not found" << std::endl;
				std::cout << "> ";
			}
			else if ((titleRange.first) == --(titleRange.second))
			{
				selectBook((*titleRange.first).second);
			}
			else
			{
				std::vector<std::unordered_map<std::string, Book>::iterator> titleBooks;
				for (auto& itbook = titleRange.first; itbook != titleRange.second; itbook++)
				{
					titleBooks.push_back(itbook);
				}
				char ch = libList(titleBooks);
			}
		}
	}
}