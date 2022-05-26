#include "book.h"

#include<iostream>


amilib::Book::Book()
	: id(0),
	ammount(0),
	title(""),
	author(""),
	size(0),
	fileName("")
{
}

amilib::Book::Book(size_t _ammount, std::string _title, std::string _author, size_t _size, std::string _fileName)
	: id(0),
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

void amilib::Book::setId(int new_id)
{
	this->id = new_id;
}

std::istream& amilib::operator>>(std::istream& in, Book& b)
{
	in >> b.id >>
	b.ammount >>
	b.title >>
	b.author >>
	b.size >>
	b.fileName;
	return in;
}

std::ostream& amilib::operator<<(std::ostream& out, Book& b)
{
	out << b.id <<
		b.ammount <<
		b.title <<
		b.author <<
		b.size <<
		b.fileName;
	return out;
}
