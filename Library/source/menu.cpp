#include "menu.h"
#include "account.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>




amilib::Menu::Menu()
{
	this->account = Account();
	this->users = UsersLoader();
	users.pull();
	this->books = BooksLoader();
	books.pull();
}

amilib::Menu::~Menu()
{
	//todo
}

void amilib::Menu::callMain()
{
	std::string role = "";
	while (role != this->account.getRole())
	{
		role = this->account.getRole();
		if (role == "unknown")
		{
			noaccMain();
		}
		else if (role == "user")
		{
			userMain();
		}
		else if (role == "admin")
		{
			adminMain();
		}
	}
}

void amilib::Menu::loadAccInfo()
{
	if (this->account.getRole() == "unknown")
	{
		return;
	}

	std::ifstream file("..\\BusinessData\\transactions.txt");
	while (!file.eof())
	{
		int userId;
		file >> userId;
		int bookId;
		file >> bookId;
		bool returned;
		file >> returned;

		if (this->account.getId() == userId && !returned)
		{
			this->account.addBook(this->books.books_map.find(bookId)->first);
		}
		if (this->account.getRole() == "admin" && !returned)
		{
			this->users.users_map.at(userId).addBook(this->books.books_map.find(bookId)->first);
		}
	}
	file.close();
}

void amilib::Menu::clearInfo()
{
	//todo
	std::cout << "\nnot implemented\n";
	system("pause");
}

void amilib::Menu::logIn()
{
	system("CLS");
	drawHeader();
    bool return_back = false;
	bool success = false;
	while (!return_back && !success)
	{
		std::cout << "Enter [x] to return back\n\n";
		std::cout << "Enter your username > ";
		std::string user_login;
		std::cin >> user_login;
		if (user_login == "x")
		{
			break;
		}
		for (std::pair<int, Account> p : this->users.users_map)
		{
			if (user_login == p.second.getLogin())
			{
				std::cout << "Hi," << user_login << "!,\nEnter your password > ";
				std::string user_password;
				std::cin >> user_password;
				while (user_password != p.second.getPassword())
				{
					std::cout << "! Not correct password !\nEnter [r] to try again\n[x] to return back\n> ";
					char ch;
					std::cin >> ch;
					if (ch == 'x')
					{
						return_back = true;
						break;
					}
					else
					{
						std::cout << "Enter your password > ";
						std::cin >> user_password;
					}
				}
				if (return_back)
				{
					break;
				}
				else
				{
					this->account.setId(p.second.getId());
					this->account.setRole(p.second.getRole());
					this->account.setLogin(p.second.getLogin());
					this->account.setPassword(p.second.getPassword());
					loadAccInfo();
					success = true;
					std::cout << "\nLogged in!\n";
					break;
				}
			}
		}
	}
}

void amilib::Menu::logOut()
{
	this->account = Account();
}

void amilib::Menu::signUp()
{
	std::cout << "not implemented" << std::endl;
}

void amilib::Menu::noaccMain()
{
	char ch = '-';
	while (ch != 'c')
	{
		system("CLS");
		drawHeader();
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		std::cout << "[l] library book list\n[i] log in\n[u] sign up\n[c] close program\n";
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		std::cout << "\n > ";
		std::cin >> ch;
		if (ch == 'l')
		{
			libBookList();
		}
		else if (ch == 'i')
		{
			logIn();
			break;
		}
		else if (ch == 'u')
		{
			signUp();
		}
	}
}

void amilib::Menu::userMain()
{
	char ch = '-';
	while (ch != 'c')
	{
		system("CLS");
		drawHeader();
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		std::cout << "[l] library book list\n[m] my list\n[o] log out\n[c] close program\n";
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		std::cout << "\n > ";
		std::cin >> ch;
		if (ch == 'l')
		{
			libBookList();
		}
		else if (ch == 'm')
		{
			userBookList();
		}
		else if (ch == 'o')
		{
			logOut();
			break;
		}
	}
}

void amilib::Menu::adminMain()
{
	char ch = '-';
	while (ch != 'c')
	{
		system("CLS");
		drawHeader();
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		std::cout << "[l] library book list\n[m] my list\n[o] log out\n[c] close program\n";
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		std::cout << "\n > ";
		std::cin >> ch;
		if (ch == 'l')
		{
			libBookList();
		}
		else if (ch == 'm')
		{
			userBookList();
		}
		else if (ch == 'o')
		{
			logOut();
			break;
		}
	}
}

void amilib::Menu::libBookList()
{
	std::vector<std::unordered_map<int, Book>::iterator> available_books;
	for (std::unordered_map<int, Book>::iterator it = books.books_map.begin(); 
		it != books.books_map.end(); it++)
	{
		if (it->second.getId() == 0) //if default book
		{
			continue;
		}
		available_books.push_back(it);
	}
	bookList(available_books);
}

void amilib::Menu::userBookList()
{
	std::vector<std::unordered_map<int, Book>::iterator> user_books;
	for (int id : this->account.acc_books)
	{
		if (id == 0) //if default book
		{
			continue;
		}
		user_books.push_back(this->books.books_map.find(id));
	}
	bookList(user_books);
}

void amilib::Menu::bookList(std::vector<std::unordered_map<int, Book>::iterator> &visible_books)
{
	system("CLS");
	drawHeader();
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	std::cout << "[x] return back\n[n] to select book\n";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	std::cout << "n\tTitle\tAuthor\n";
	std::cout << "-----------------------------------------------\n";
	for (size_t i = 0; i < visible_books.size(); i++)
	{
		std::cout << "[" << i << "]\t" << visible_books[i]->second.getTitle() << "\t"
			<< visible_books[i]->second.getAuthor() << "\n";
	}
	std::cout << "-----------------------------------------------\n";
	std::cout << "n\tTitle\tAuthor\n";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	std::cout << "[x] return back\n[n] to select book\n";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	std::cout << "\n > ";
	std::string user_input;
	std::cin >> user_input;
	if (user_input == "x")
	{
		return;
	}
	else
	{
		selectBook(visible_books[std::stoi(user_input)]->second);
	}
}

void amilib::Menu::selectBook(Book& book_to_select)
{
	char ch = '-';
	while (ch != 'x')
	{
		system("CLS");
		drawHeader();
		std::cout << "Title\t" << book_to_select.getTitle() << "\n";
		std::cout << "Author\t" << book_to_select.getAuthor() << "\n";
		std::cout << "Pages\t" << book_to_select.getSize() << "\n";
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		bool book_is_taken = this->account.hasABook(book_to_select.getId());
		if (book_is_taken)
		{
			std::cout << "[r] read book\n[b] return the book\n";
		}
		else
		{
			std::cout << "[t] take book\n";
		}
		if (this->account.getRole() == "admin")
		{
			std::cout << "[e] open in editor\n";
		}
		std::cout << "[x] return back\n";
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		std::cout << "\n > ";
		std::cin >> ch;
		if (book_is_taken)
		{
			if (ch == 'r')
			{
				//todo
				std::cout << "\nnot implemented\n";
				system("pause");
			}
			else if (ch == 'b')
			{
				returnBook(book_to_select.getId());
			}
		}
		else if (ch == 't')
		{
			takeBook(book_to_select.getId());
		}
		if (this->account.getRole() == "admin")
		{
			if (ch == 'e')
			{
				//todo
				std::cout << "\nnot implemented\n";
				system("pause");
			}
		}
	}
}

void amilib::Menu::drawHeader()
{
	std::cout << "Amilib by AMi-11" << std::endl;
	std::cout << "==================================================================================\n";
	std::cout << this->account.getLogin() << "\n";
	std::cout << "==================================================================================\n\n";
}

void amilib::Menu::bookSearch()
{
	//todo
	std::cout << "\nnot implemented\n";
	system("pause");
}

void amilib::Menu::updateUsers()
{
	//todo
	std::cout << "\nnot implemented\n";
	system("pause");
}

void amilib::Menu::updateBooks()
{
	//todo
	std::cout << "\nnot implemented\n";
	system("pause");
}

void amilib::Menu::takeBook(int book_id)
{
	//? update?
	size_t ammount = this->books.books_map.at(book_id).getAmmount();
	if (ammount == 0)
	{
		//todo : throw
	}
	else
	{
		this->books.books_map.at(book_id).setAmmount(--ammount);
	}
	this->account.addBook(book_id);
	std::fstream file("..\\BusinessData\\transactions.txt", std::ios::app);
	file << "\n" << this->account.getId() << ' ' << book_id << ' ' << 0;
	file.close();
	//? update?
	std::cout << "Book is taken\n";
}

void amilib::Menu::returnBook(int book_id)
{
	size_t ammount = this->books.books_map.at(book_id).getAmmount();
	this->books.books_map.at(book_id).setAmmount(++ammount);
	this->account.removeBook(book_id);
	std::fstream file("..\\BusinessData\\transactions.txt", std::ios::out | std::ios::in);
	while (!file.eof())
	{
		int userId;
		file >> userId;
		int bookId;
		file >> bookId;
		bool returned;
		file >> returned;
		if (userId == this->account.getId() && bookId == book_id && !returned)
		{
			int pos = file.tellg();
			file.seekp(pos - 1);
			file << 1;
			break;
		}
	}
	file.close();
	std::cout << "Book is returned\n";
}
