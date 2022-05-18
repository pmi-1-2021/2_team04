#include "book.h"




amilib::Book::Book(int _id, size_t _ammount, std::string _title, std::string _author, size_t _size, std::string _fileName)
	: id(_id),
	ammount(_ammount),
	title(_title),
	author(_author),
	size(_size),
	fileName(_fileName)
{
}

int amilib::Book::getId()
{
	return id;
}

size_t amilib::Book::getAmmount()
{
	return ammount;
}

size_t amilib::Book::getSize()
{
	return size;
}

std::string amilib::Book::getTitle()
{
	return title;
}

std::string amilib::Book::getAuthor()
{
	return author;
}

std::string amilib::Book::getFileName()
{
	return fileName;
}

void amilib::Book::setAmmount(size_t new_ammount)
{
	ammount = new_ammount;
}
