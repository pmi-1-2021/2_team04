#include "database.h"

#include <sstream>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <map>


std::string getAmmountOffset(size_t ammount);

amilib::BooksDataBase::BooksDataBase(std::string info_file_path)
	:infoFilePath(info_file_path)
{
}

amilib::BooksDataBase::~BooksDataBase()
{
	//todo
}


void amilib::BooksDataBase::pull(std::unordered_map<int , Book>& books_map)
{
	std::ifstream file(infoFilePath);
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

		Book b(ammount, title, author, size, fileName);
		b.setId(id);
		books_map.emplace(std::make_pair(id, b));
	}
	file.close();
}

//void amilib::BooksDataBase::addItem(Book b)
//{
//	std::string os = "";
//	size_t i = 1000;
//	for ( ; i > 9; i = i / 10)
//	{
//		if (b.getAmmount() % i == b.getAmmount())
//		{
//			os += "0";
//		}
//		else
//		{
//			break;
//		}
//	}
//	std::fstream file(infoFilePath, std::ios::out | std::ios::app);
//	file << b.getId() << ' ' << os << b.getAmmount() << ' ' << b.getTitle() << ' ' << b.getAuthor() << ' ' << b.getSize() << ' ' << b.getFileName() << "\n";
//	file.close();
//}

void amilib::BooksDataBase::changeBookAmmount(int book_id, size_t new_ammount)
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

void amilib::BooksDataBase::changeBookInfo(int book_id, Book new_info)
{
	std::map<int, Book> books;
	std::ifstream file(infoFilePath);
	while (!file.eof())
	{
		Book b;
		file >> b;
		if (b.getId() != 0)
		{
			books[b.getId()] = b;
		}
	}
	file.close();
	books.at(book_id) = new_info;
	std::ofstream overwtire;
	overwtire.open(infoFilePath);
	for (auto& pair : books)
	{
		overwtire << pair.second.getId() << ' ' 
			<< getAmmountOffset(pair.second.getAmmount())
			<< pair.second.getAmmount() << ' '
			<< pair.second.getTitle() << ' ' << pair.second.getAuthor() << ' '
			<< pair.second.getSize() << ' ' << pair.second.getFileName() << "\n";
	}
	overwtire.close();
}

void amilib::BooksDataBase::addNewBook(Book b)
{
	std::fstream file(infoFilePath, std::ios::out | std::ios::app);
	file << b.getId() << ' ' << getAmmountOffset(b.getAmmount()) << b.getAmmount() << ' ' << b.getTitle() << ' ' << b.getAuthor() << ' ' << b.getSize() << ' ' << b.getFileName() << "\n";
	file.close();
}

void amilib::BooksDataBase::takeBook(int user_id, int book_id)
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

void amilib::BooksDataBase::returnBook(int user_id, int book_id)
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
			file << getAmmountOffset(++ammount) << ammount;
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

int amilib::BooksDataBase::createId()
{
	//read file backwards untill begining of the last line(id)
	std::ifstream file(infoFilePath);
	file.seekg(-3, std::ios_base::end);// skip last /n
	char ch;
	bool keepLooping = true;
	while (keepLooping) {
		file.get(ch);                         
		if ((int)file.tellg() <= 1) {       
			file.seekg(0);                  
			keepLooping = false;             
		}
		else if (ch == '\n') {                   
			keepLooping = false;                
		}
		else {                                
			file.seekg(-2, std::ios_base::cur);
		}
	}
	int lastId;
	file >> lastId;
	file.close();
	return ++lastId;
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
