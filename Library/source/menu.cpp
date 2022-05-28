#include "menu.h"
#include "account.h"
#include "booklist.h"
#include "bookstaking.h"
#include "global_transactions.h"
#include "book_transactions.h"
#include "user_transactions.h"
#include "book_menu.h"

#include <iostream>
#include <fstream>
#include <stdlib.h>




amilib::Library::Library(BooksDataBase books_data_base, UsersDataBase users_data_base)
	: account(),
	usersDB(users_data_base),
	booksDB(books_data_base),
	usersMap(),
	booksMap()
{
	this->booksDB.pull(this->booksMap);
}

amilib::Library::~Library()
{
	std::cout << "[Debug] ~Destructor() menu";
	//todo
}

void amilib::Library::callMenu()
{
	std::string role = "";
	while (role != this->account.getRole())
	{
		role = this->account.getRole();
		if (role == "unknown")
		{
			noaccMenu();
		}
		else if (role == "user")
		{
			userMenu();
		}
		else if (role == "admin")
		{
			adminMenu();
		}
	}
}

void amilib::Library::loadAccInfo()
{
	if (this->account.getRole() == "unknown")
	{
		return;
	}
	BooksTakingBase takings("..\\BusinessData\\takings.txt");
	takings.fillAccount(this->account);
	if (this->account.getRole() == "admin")
	{
		takings.fillAllAccounts(this->usersMap);
	}
	else
	{
		this->usersMap.clear();
	}
}

void amilib::Library::clearInfo()
{
	//todo
	throw std::string("not implemented");
	system("pause");
}

void amilib::Library::changeBookAmmount(int book_id, size_t new_ammount)
{
	this->booksMap.at(book_id).setAmmount(new_ammount);
}

void amilib::Library::changeBookInfo(int book_id, Book new_info)
{
	try
	{
		this->booksMap.at(book_id) = new_info;
	}
	catch (const std::exception&)
	{
		throw std::string("Book with id = '" + std::to_string(book_id) + "' was not found in Menu::booksMap");
	}
}

void amilib::Library::takeBook(int user_id, int book_id)
{
	this->account.addBook(book_id, false);
	if (this->account.getRole() == "admin")
	{
		try
		{
			this->usersMap.at(user_id).addBook(book_id, true);
		}
		catch (const std::exception&)
		{
			throw std::string("User with id = '" + std::to_string(book_id) + "' was not found in Menu::booksMap");
		}
	}
}

void amilib::Library::returnBook(int user_id, int book_id)
{
	this->account.returnBook(book_id);
	if (this->account.getRole() == "admin")
	{
		try
		{
			this->usersMap.at(user_id).returnBook(book_id);
		}
		catch (const std::exception&)
		{
			throw std::string("User with id = '" + std::to_string(book_id) + "' was not found in Menu::booksMap");
		}
	}
}

void amilib::Library::addNewBook(Book b)
{
	this->booksMap.insert({ b.getId(), b });
}

bool amilib::Library::logInForm()
{
	system("CLS");
	drawHeader();
	this->usersDB.pull(this->usersMap);
	bool loggedIn = false;
	while (!loggedIn)
	{
		std::cout << "Enter [x] to return back\n\n";
		std::cout << "Enter your username > ";
		std::string entered_username;
		std::cin.clear();
		std::cin >> entered_username;
		if (entered_username == "x")
		{
			break;
		}
		int id = idAtUsernameInMap(entered_username);
		if (id == 0)
		{
			std::cout << "\Account with this username does not exist!\n";
		}
		else
		{
			Account& a = this->usersMap.at(id);
			loggedIn = askPassword(a);
			if (loggedIn)
			{
				this->account = a;
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

void amilib::Library::logOut()
{
	this->account = Account();
}

void amilib::Library::signUpForm()
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
	bool unique = true;
	std::string new_username;
	do
	{
		unique = true;
		std::cout << "\nEnter [x] to cancel creating new account\nRegistration:\nEnter username:\n > ";
		std::cin >> new_username;
		if (new_username == "x")
		{
			return;
		}
		unique = !this->usersDB.isExist(new_username);
		if (!unique)
		{
			std::cout << "\nThis username is unavailable\n";
		}
	} while (!unique);
	std::cout << "\nEnter new password:\n > ";
	std::string new_password;
	std::cin >> new_password;
	if (new_password == "x")
	{
		return;
	}
	Account a(new_role, new_username, new_password);
	CreateTransaction* factory = new CreateAddUserTransaction(a);
	GlobalFileTransaction* t = factory->createBy(this->account.getId());
	t->execute();
	delete factory;
	delete t;
	std::cout << "Account is successfully created!\n Press enter to go back\n > ";
	std::cin.ignore();
	std::cin.ignore();
}

void amilib::Library::noaccMenu()
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
			if (logInForm())
			{
				break;
			}
		}
		else if (ch == 'u')
		{
			signUpForm();
		}
	}
}

void amilib::Library::userMenu()
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

void amilib::Library::adminMenu()
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
			newBookForm();
		}
		else if (ch == 'a')
		{
			signUpForm();
		}
		else if (ch == 'o')
		{
			logOut();
			break;
		}
	}
}

void amilib::Library::libBookList()
{
	std::vector<Book> available_books;
	for (std::unordered_map<int, Book>::iterator it = booksMap.begin(); 
		it != booksMap.end(); it++)
	{
		if (it->second.getAmmount() != 0)
		{
			available_books.push_back(it->second);
		}
	}
	bookList(available_books);
}

void amilib::Library::userBookList()
{
	std::vector<Book> acc_books;
	for (std::vector<std::pair<int, bool>>::iterator it = this->account.acc_books.begin();
		it != this->account.acc_books.end(); it++)
	{
		if (!it->second)
		{
			acc_books.push_back(this->booksMap.at(it->first));
		}
	}
	bookList(acc_books);
}

void amilib::Library::bookList(std::vector<Book> &visible_books)
{
	system("CLS");
	drawHeader();
	BookList list(visible_books);
	list.draw();
	int id = 0;
	while (list.askId(id))
	{
		selectBook(booksMap.at(id));
		system("CLS");
		drawHeader();
		list.draw();
	}
}

void amilib::Library::selectBook(Book& book_to_select)
{
	bool book_is_taken = this->account.hasABook(book_to_select.getId());
	BookMenu bm(book_to_select, this->account.getRole(), book_is_taken);
	do
	{
		bm.draw();
		char ch = bm.getAction();
		if (ch == 'r')
		{
			//todo
			std::cout << "\nnot implemented\n";
			system("pause");
		}
		else if (ch == 'b')
		{
			transactionReturnBook(book_to_select.getId());
			bm.setIsBookTaken(false);
			std::cout << "\nPress enter to continue\n > ";
			std::cin.ignore();
			std::cin.ignore();
		}
		else if (ch == 't')
		{
			transactionTakeBook(book_to_select.getId());
			bm.setIsBookTaken(true);
			std::cout << "\nPress enter to continue\n > ";
			std::cin.ignore();
			std::cin.ignore();
		}
		else if (ch == 'e')
		{
			editBookForm(book_to_select);
		}
	} while (!bm.exitKey());
}

void amilib::Library::drawHeader()
{
	std::cout << "Amilib by AMi-11" << std::endl;
	std::cout << "==================================================================================\n";
	std::cout << this->account.getUsername() << "\n";
	std::cout << "==================================================================================\n\n";
}

void amilib::Library::bookSearch()
{
	//todo
	throw "not implemented";
}


void amilib::Library::transactionTakeBook(int book_id)
{
	if (this->account.getRole() == "unknown")
	{
		std::cout << "Please, log in or create an account to take this book\n Press enter to continue\n > ";
		std::cin.ignore();
		std::cin.ignore();
		return;
	}
	CreateTransaction* factory = new CreateTakeBookTransaction(book_id);
	GlobalFileTransaction* t = factory->createBy(this->account.getId());
	delete factory;
	t->execute();
	delete t;
}

void amilib::Library::transactionReturnBook(int book_id)
{
	CreateTransaction* factory = new CreateReturnBookTransaction(book_id);
	GlobalFileTransaction* t = factory->createBy(this->account.getId());
	delete factory;
	t->execute();
	delete t;
}

void amilib::Library::newBookForm()
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
	Book b (new_ammount, new_title, new_athor, new_size, new_file_name);
	CreateTransaction* factory = new CreateAddBookTransaction(b);
	GlobalFileTransaction* addBook = factory->createBy(this->account.getId());
	addBook->execute();
	std::cout << "New book was successfully added!\nPress enter to go back\n > ";
	std::cin.ignore();
	std::cin.ignore();
}

void amilib::Library::editBookForm(Book b)
{
	system("CLS");
	std::cout << "Title\t" << b.getTitle() << "\n";
	std::cout << "Author\t" << b.getAuthor() << "\n";
	std::cout << "Pages\t" << b.getSize() << "\n";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	std::cout << "\nEnter [x] to cancel editing\n"
		"Enter[t] to change title\n"
		"Enter[a] to change author\n"
		"Enter[p] to change pages size\n";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	std::cout << " > ";
	char ch;
	std::cin >> ch;
	std::cout << "\nChange to: \n > ";
	std::string newInfo;
	std::cin >> newInfo;
	if (ch == 'x')
	{
		return;
	}
	else if (ch == 't')
	{
		b.setTitle(newInfo);
	}
	else if (ch == 'a')
	{
		b.setAuthor(newInfo);
	}
	else if (ch == 'p')
	{
		size_t newSize = std::stoul(newInfo);
		b.setSize(newSize);
	}

	CreateTransaction* factory = new CreateChangeBookInfoTransaction(b.getId(), b);
	GlobalFileTransaction* addBook = factory->createBy(this->account.getId());
	addBook->execute();
	std::cout << "The book's info was successfully changed!\nPress enter to go back\n > ";
	std::cin.ignore();
	std::cin.ignore();
}

//bool amilib::Menu::uniqueNewUsername(std::string name)
//{
//	bool unique = true;
//	for (std::unordered_map<int, Account>::iterator it = usersMap.begin();
//		it != usersMap.end(); it ++)
//	{
//		if (it->second.getUsername() == name)
//		{
//			unique = false;
//		}
//	}
//	return unique;
//}

int amilib::Library::idAtUsernameInMap(std::string name)
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

bool amilib::Library::askPassword(Account& a)
{
	system("CLS");
	std::cout << "[x] to return to menu\nHi," << a.getUsername() 
		<< "!\nEnter your password:\n";
	std::string entered_password;
	do
	{
		std::cout << "\n > ";
		std::cin >> entered_password;
		if (entered_password == "x")
		{
			return false;
		}
		if (entered_password != a.getPassword())
		{
			std::cout << "\n! Not correct password !\n";
		}
	} while (entered_password != a.getPassword());
	return true;
}

std::string amilib::Library::createFileName(std::string from)
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
