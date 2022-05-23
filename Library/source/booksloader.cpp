#include "infoLoaders.h"

#include <fstream>
#include <map>


std::string getAmmountOffset(size_t ammount);

amilib::BooksLoader::BooksLoader(std::string info_file_path)
	:infoFilePath(info_file_path)
{
}

amilib::BooksLoader::~BooksLoader()
{
	//todo
}


void amilib::BooksLoader::pull(std::unordered_map<int , Book>& books_map)
{
	std::ifstream file("..\\BusinessData\\booksInfo.txt");
	while (!file.eof())
	{
		int id;
		file >> id;
		size_t ammount;
		file >> ammount;
		std::string title;
		file >> title;
		std::string author;
		file >> author;
		size_t size;
		file >> size;
		std::string fileName;
		file >> fileName;

		books_map.emplace(std::make_pair(id, Book(id, ammount, title, author, size, fileName)));
	}
	file.close();
}

void amilib::BooksLoader::addItem(Book b)
{
	std::string os = "";
	size_t i = 1000;
	for ( ; i > 9; i = i / 10)
	{
		if (b.getAmmount() % i == b.getAmmount())
		{
			os += "0";
		}
		else
		{
			break;
		}
	}
	std::fstream file("..\\BusinessData\\booksInfo.txt", std::ios::out | std::ios::app);
	file << b.getId() << ' ' << os << b.getAmmount() << ' ' << b.getTitle() << ' ' << b.getAuthor() << ' ' << b.getSize() << ' ' << b.getFileName() << "\n";
	file.close();
}

void amilib::BooksLoader::changeBookAmmount(int book_id, size_t new_ammount)
{
	std::fstream file(infoFilePath, std::ios::out | std::ios::in);
	while (!file.eof())
	{
		int id;
		file >> id;
		if (book_id == id)
		{
			int pos = (int)file.tellg();
			file.seekp(pos + 1);
			file << getAmmountOffset(new_ammount) << new_ammount;
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

void amilib::BooksLoader::changeBookInfo(int book_id, Book new_info)
{
	std::map<int, Book> books;
	std::ifstream file(infoFilePath);
	while (!file.eof())
	{
		Book b;
		file >> b;
		books[b.getId()] = b;
	}
	file.close();
	books.at(book_id) = new_info;
	std::ofstream overwtire;
	overwtire.open(infoFilePath);
	for (std::map<int, Book>::iterator it = books.begin();
		it != books.end(); it++)
	{
		overwtire << it->second << "\n";
	}
	overwtire.close();
}

void amilib::BooksLoader::addNewBook(Book b)
{
	std::fstream file(infoFilePath, std::ios::out | std::ios::app);
	file << b.getId() << ' ' << getAmmountOffset(b.getAmmount()) << b.getAmmount() << ' ' << b.getTitle() << ' ' << b.getAuthor() << ' ' << b.getSize() << ' ' << b.getFileName() << "\n";
	file.close();
}

void amilib::BooksLoader::takeBook(int user_id, int book_id)
{
	std::fstream file(infoFilePath, std::ios::out | std::ios::in);
	while (!file.eof())
	{
		int id;
		file >> id;
		if (book_id == id)
		{
			int pos = (int)file.tellg() + 1;
			size_t ammount;
			file >> ammount;
			file.seekp(pos);
			file << getAmmountOffset(--ammount) << ammount;
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

void amilib::BooksLoader::returnBook(int user_id, int book_id)
{
	std::fstream file(infoFilePath, std::ios::out | std::ios::in);
	while (!file.eof())
	{
		int id;
		file >> id;
		if (book_id == id)
		{
			int pos = (int)file.tellg() + 1;
			size_t ammount;
			file >> ammount;
			file.seekp(pos);
			file << getAmmountOffset(++ammount) << ++ammount;
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

std::string getAmmountOffset(size_t ammount)
{
	std::string os = "";
	size_t i = 1000;
	for (; i > 9; i = i / 10)
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
	return os;
}
