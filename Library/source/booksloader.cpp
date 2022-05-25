#include "infoLoaders.h"

#include <fstream>



amilib::BooksLoader::BooksLoader()
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
