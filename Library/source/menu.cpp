#include "menu.h"
#include "account.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>




amilib::Menu::Menu() 
	: account(),
	booksMap(),
	usersInfo(),
	usersMap()
{
	/*this->account = Account();
	this->usersInfo = UsersLoader();*/
	this->usersInfo.pull(usersMap);
	this->booksInfo.pull(booksMap);
	//this->books = BooksLoader();
	//books.pull();
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
		if (userId == 0)
		{
			continue;
		}
		if (this->account.getId() == userId && !returned)
		{
			this->account.addBook(this->booksMap.find(bookId)->first);
		}
		if (this->account.getRole() == "admin" && !returned)
		{
			this->usersMap.at(userId).addBook(this->booksMap.find(bookId)->first);
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

bool amilib::Menu::logIn()
{
	system("CLS");
	drawHeader();
	bool loggedIn = false;
	while (!loggedIn)
	{
		std::cout << "Enter [x] to return back\n\n";
		std::cout << "Enter your username > ";
		std::string entered_username;
		std::cin >> entered_username;
		if (entered_username == "x")
		{
			break;
		}
		int id = idAtUsername(entered_username);
		if (id == 0)
		{
			std::cout << "Incorrect username!\nEnter [r] to try again\n[x] to return back\n >";
			char ch;
			std::cin >> ch;
			if (ch == 'r')
			{
				continue;
			}
			else if (ch == 'x')
			{
				break;
			}
		}
		else
		{
			Account& a = this->usersMap.at(id);
			loggedIn = askPassword(a);
			if (loggedIn)
			{
				this->account.setId(a.getId());
				this->account.setRole(a.getRole());
				this->account.setUsername(a.getUsername());
				this->account.setPassword(a.getPassword());
				loadAccInfo();
				system("CLS");
				std::cout << "\nLogged in!\n Press enter to continue\n > ";
				std::cin.ignore();
				std::cin.ignore();
			}
			else
			{
				break;
			}
		}
	}

	return loggedIn;
}

void amilib::Menu::logOut()
{
	this->account = Account();
}

void amilib::Menu::signUp()
{
	system("CLS");
	std::string new_role;
	if (this->account.getRole() == "admin")
	{
		std::cout << "Add a new admin:\n";
		new_role = "admin";
	}
	else
	{
		new_role = "user";
	}
	bool go_back = false;
	bool unique = true;
	std::string new_username;
	do
	{
		unique = true;
		std::cout << "\nEnter [x] to cancel adding\nRegistration:\nEnter username:\n > ";
		std::cin >> new_username;
		if (new_username == "x")
		{
			return;
		}
		unique = uniqueNewUsername(new_username);
		if (!unique)
		{
			std::cout << "\nThis username is unavailable\n[x] to go back\n[r] to try another username\n > ";
			char ch;
			std::cin >> ch;
			if (ch == 'x')
			{
				go_back = true;
				break;
			}
			else if (ch == 'r')
			{
				system("CLS");
			}
			system("CLS");
		}
	} while (!unique);
	if (go_back)
	{
		return;
	}
	std::unordered_map<int, Account>::iterator it = --this->usersMap.end();
	int new_id = (int)(it->first) + 1;
	std::cout << "\nEnter new password:\n > ";
	std::string new_password;
	std::cin >> new_password;
	if (new_username == "x")
	{
		return;
	}
	Account a(new_id, new_role, new_username, new_password);
	usersMap.insert({ new_id, a });
	usersInfo.addItem(a);
	std::cout << "Account is successfully created!\n Press enter to go back\n > ";
	std::cin.ignore();
	std::cin.ignore();
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
			if (logIn())
			{
				break;
			}
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
		std::cout << "[l] library book list\n[m] my list\n[b] add new book\n[a] add new admin\n[o] log out\n[c] close program\n";
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
		else if (ch == 'b')
		{
			addNewBook();
		}
		else if (ch == 'a')
		{
			signUp();
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
	for (std::unordered_map<int, Book>::iterator it = booksMap.begin(); 
		it != booksMap.end(); it++)
	{
		if (it->second.getAmmount() != 0)
		{
			available_books.push_back(it);
		}
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
		user_books.push_back(this->booksMap.find(id));
	}
	bookList(user_books);
}

void amilib::Menu::bookList(std::vector<std::unordered_map<int, Book>::iterator> &visible_books)
{
	system("CLS");
	drawHeader();
	if (visible_books.size() == 0)
	{
		std::cout << "You are not reading any books yet, go to the library book list, to chose one to read\n Press enter to go back\n > ";
		std::cin.ignore();
		std::cin.ignore();
		return;
	}
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
	if (visible_books.size() > 35)
	{
		std::cout << "-----------------------------------------------\n";
		std::cout << "n\tTitle\tAuthor\n";
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
		std::cout << "[x] return back\n[n] to select book\n";
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	}
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
	std::cout << this->account.getUsername() << "\n";
	std::cout << "==================================================================================\n\n";
}

void amilib::Menu::bookSearch()
{
	//todo
	throw "not implemented";
}


void amilib::Menu::takeBook(int book_id)
{
	//? update?
	if (this->account.getRole() == "unknown")
	{
		std::cout << "Please, log in or create an account to take this book\n Press enter to continue\n > ";
		std::cin.ignore();
		std::cin.ignore();
		return;
	}
	size_t ammount = this->booksMap.at(book_id).getAmmount();
	if (ammount == 0)
	{
		//todo : throw
	}
	else
	{
		this->booksMap.at(book_id).setAmmount(--ammount);
		std::string os = "";
		size_t i = 1000;
		for ( ; i > 9; i/10)
		{
			if (ammount % i == ammount)
			{
				os += "0";
			}
			else
			{
				break;
			}
		}
		std::fstream file("..\\BusinessData\\booksInfo.txt", std::ios::out | std::ios::in);
		while (!file.eof())
		{
			int id;
			file >> id;
			if (book_id == id)
			{
				int pos = (int)file.tellg();
				file.seekp(pos + 1);
				file << os << ammount;
				break;
			}
			else
			{
				char skipLine[200];
				file.getline(skipLine, 200, '\n');
			}
		}
		file.close();
	}
	this->account.addBook(book_id);
	std::fstream file("..\\BusinessData\\transactions.txt", std::ios::app);
	file << this->account.getId() << ' ' << book_id << ' ' << 0 << "\n";
	file.close();
	//? update?
	std::cout << "Book is taken\n";
}

void amilib::Menu::returnBook(int book_id)
{
	size_t ammount = this->booksMap.at(book_id).getAmmount();
	this->booksMap.at(book_id).setAmmount(++ammount);
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
			int pos = (int)file.tellg();
			file.seekp(pos - 1);
			file << 1;
			break;
		}
	}
	file.close();
	std::cout << "Book is returned\n";
}

void amilib::Menu::addNewBook()
{
	system("CLS");
	std::cout << "\nEnter [x] to cancel adding\nEnter the title:\n > ";
	std::string new_title;
	std::cin >> new_title;
	if (new_title == "x")
	{
		return;
	}
	std::cout << "\nEnter [x] to cancel adding\nEnter the athor:\n > ";
	std::string new_athor;
	std::cin >> new_athor;
	if (new_athor == "x")
	{
		return;
	}
	std::cout << "\nEnter [x] to cancel adding\nEnter the size in pages:\n > ";
	size_t new_size;
	std::cin >> new_size;
	if (new_size == 'x')
	{
		return;
	}
	std::cout << "\nEnter [x] to cancel adding\nEnter the ammount of copies of the book:\n > ";
	size_t new_ammount;
	std::cin >> new_ammount;
	if (new_ammount == 'x')
	{
		return;
	}
	std::string new_file_name(createFileName(new_title + new_athor));
	int new_id = (--(this->booksMap.end()))->first + 1;
	Book b (new_id, new_ammount, new_title, new_athor, new_size, new_file_name);
	this->booksMap.insert({ new_id, b });
	booksInfo.addItem(b);
	std::cout << "New book was successfully added!\n Press enter to go back\n > ";
	std::cin.ignore();
	std::cin.ignore();
}

bool amilib::Menu::uniqueNewUsername(std::string name)
{
	bool unique = true;
	for (std::unordered_map<int, Account>::iterator it = usersMap.begin();
		it != usersMap.end(); it ++)
	{
		if (it->second.getUsername() == name)
		{
			unique = false;
		}
	}
	return unique;
}

int amilib::Menu::idAtUsername(std::string name)
{
	std::unordered_map<int, Account>::iterator it = usersMap.begin();
	for ( ; it != usersMap.end(); it++)
	{
		if (it->second.getUsername() == name)
		{
			return it->second.getId();
		}
	}
	return 0;
}

bool amilib::Menu::askPassword(Account& a)
{
	std::cout << "Hi," << a.getUsername() << "!\nEnter your password > ";
	std::string entered_password;
	std::cin >> entered_password;
	while (entered_password != a.getPassword())
	{
		std::cout << "! Not correct password !\nEnter [r] to try again\n[x] to return back\n > ";
		char ch;
		std::cin >> ch;
		if (ch == 'x')
		{
			return false;
		}
		else
		{
			std::cout << "Enter your password > ";
			std::cin >> entered_password;
		}
	}
	return true;
}

std::string amilib::Menu::createFileName(std::string from)
{
	for (auto it = from.begin(); it < from.end(); it++)
	{
		if (*it == ' ')
		{
			from.erase(it);
		}
	}
	return from;
}
