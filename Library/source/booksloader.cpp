#include "infoLoaders.h"

#include <fstream>



amilib::BooksLoader::BooksLoader()
{
	pull();
}

amilib::BooksLoader::~BooksLoader()
{
	//todo
}


void amilib::BooksLoader::pull()
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

		this->books_map.emplace(std::make_pair(id, Book(id, ammount, title, author, size, fileName)));
	}
}